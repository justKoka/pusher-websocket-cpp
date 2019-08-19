#include "pushcpp_internal.h"

pushcpp::pushcpp(
	const string &wsUrl,
	const string &userAgent,
	ConnectionEventHandler ch,
	ErrorEventHandler eh
)
{
	this->m_connectionEventHandler = ch;
	this->m_errorEventHandler = eh;
	this->m_userAgent = userAgent;
	stringstream str;
	str << "ws://";
	str << wsUrl;
	str << "?client=pushcpp&version=1.0&protocol=5";
	m_url = str.str();
}

void pushcpp::connect()
{
	DEBUG("Connecting.");
	assert(!this->m_eventThread);
	m_eventThread = new thread(&pushcpp::EventThread, this);
	assert(this->m_eventThread);
}

bool pushcpp::connected() const
{
	return
		this->m_websocket != NULL && (
			((WebSocket::pointer) this->m_websocket)->
			getReadyState() == WebSocket::OPEN
		);
}

void pushcpp::disconnect(bool wait)
{
	m_wantDisconnect = true;
	if (wait && m_eventThread)
		m_eventThread->join();
}

void pushcpp::join()
{
	assert(this->m_eventThread);
	DEBUG("joining!");
	m_eventThread->join();
}

bool pushcpp::sendRaw(const string &raw)
{
	WebSocket::pointer ws = (WebSocket::pointer) this->m_websocket;

	if (ws != NULL && ws->getReadyState() == WebSocket::OPEN) {
		DEBUG("send: %s", raw.c_str());
		ws->send(raw);
		return true;
	}

	return false;
}

bool pushcpp::send(
	const string &channel,
	const string &event,
	const string &data
)
{
	json_t *json = json_object();
	json_object_set_new(json, "event", json_string(event.c_str()));

	if (channel != "")
		json_object_set_new(json, "channel", json_string(channel.c_str()));

	json_object_set_new(json, "data", json_string(data.c_str()));
	char *dumped = json_dumps(json, 0);
	assert(dumped);
	json_decref(json);

	bool ret = sendRaw(dumped);
	free(dumped);
	return ret;
}

void pushcpp::cn_ev(const pushcpp::ConnectionEvent ev)
{
	printf("ConnectEvent: %d\n", ev);
}

void pushcpp::er_ev(const int code, const std::string &msg)
{
	std::cout << "Error from pusher: " << code << " " << msg << std::endl;
}


void pushcpp::event_handler(
	const string &channel,
	const string &event,
	const string &data
)
{
	cout << "event: " << event << endl << "on channel: " << channel << endl << "with data: " << data << endl;
}

pushcpp::ChannelAuthentication pushcpp::auth_handler(const std::string &socketId, const std::string &channel, const std::string &userAgent, const std::string &hostAuthEndpoint, const unsigned int &portAuthEndpoint, const std::string &pathAuthEndpoint, const std::string &token)
{
	char httpPostResponse[128];

	//setup connection, make request

	HINTERNET hInternet = InternetOpen(userAgent.c_str(), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);
	if (hInternet != NULL) {
		HINTERNET hConnect = InternetConnect(hInternet, hostAuthEndpoint.c_str(), portAuthEndpoint, NULL, NULL, INTERNET_SERVICE_HTTP, NULL, NULL);
		if (hConnect != NULL) {
			LPCSTR rgpszAcceptTypes[] = { "*/*", NULL };
			HINTERNET hRequest = HttpOpenRequest(hConnect, "POST", pathAuthEndpoint.c_str(), NULL, NULL, rgpszAcceptTypes, NULL, NULL);
			if (hRequest != NULL) {
				unique_ptr<char[]> httpHeaders(new char[81 + token.length()]);
				sprintf(httpHeaders.get(), "Accept: application/json\r\nContent-Type: application/json\r\nAuthorization: Bearer %s", token.c_str());

				//making post data to send via http (json including socketId and channel)

				unique_ptr<char[]> PostData(new char[44 + socketId.length() + channel.length()]);
				sprintf(PostData.get(), "{ \"socket_id\": \"%s\", \"channel_name\": \"%s\" }", socketId.c_str(), channel.c_str());
				bool res = HttpSendRequest(hRequest, LPCSTR(httpHeaders.get()), strlen(httpHeaders.get()), (LPVOID)PostData.get(), strlen(PostData.get()));
				//for debugging

				char queryInfo[2056];
				DWORD queryInfoLength = strlen(queryInfo);
				DWORD index = 0;
				HttpQueryInfo(hRequest, HTTP_QUERY_RAW_HEADERS_CRLF, queryInfo, &queryInfoLength, &index);
				auto prob = GetLastError();

				//reading response

				DWORD bytesRead = 0;
				res = InternetReadFile(hRequest, httpPostResponse, strlen(httpPostResponse), &bytesRead);

				//closing handles, ending http session

				InternetCloseHandle(hRequest);
			}
			InternetCloseHandle(hConnect);
		}
		InternetCloseHandle(hInternet);
	}

	//extracting authorization key

	constexpr char AUTH[] = "auth\":\"";
	char *authStart = strstr(httpPostResponse, AUTH) + strlen(AUTH);
	char *authEnd = strstr(authStart, "\"");
	unique_ptr<char[]> authKey(new char[authEnd - authStart + 1]);
	strncpy(authKey.get(), authStart, authEnd - authStart);
	(authKey.get())[authEnd - authStart] = '\0';
	pushcpp::ChannelAuthentication channelAuthentication;
	channelAuthentication.auth = authKey.get();
	return channelAuthentication;
}