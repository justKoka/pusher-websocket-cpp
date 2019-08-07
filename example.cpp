#include "pushcpp.h"
#include <iostream>
#include <Windows.h>
//#include <curl/curl.h>
#include <wininet.h>
#pragma comment(lib,"wininet")
using namespace std;

void cn_ev(const pushcpp::ConnectionEvent ev);
void er_ev(const int code, const std::string &msg);
//size_t write_callback(char *, size_t, size_t, void *);

pushcpp pp("app/key", cn_ev, er_ev);

void cn_ev(const pushcpp::ConnectionEvent ev)
{
	printf("ConnectEvent: %d\n", ev);
}

void er_ev(const int code, const std::string &msg)
{
	cout << "Error from pusher: " << code << " "  << msg << endl;
}

void sub_ev(
	const string &channel,
	const string &event,
	const string &data
)
{
	// cout << pp.subscriptions().size() << endl;

	printf("Received event %s on channel %s: %s\n",
		   event.c_str(), channel.c_str(), data.c_str());

	auto cd = pp.subscriptions();

	cout << "Subs: " << endl;
	for (
		auto it = cd.begin();
		it != cd.end();
		it++
	) {
		cout << "Subscription: " << it->first <<
			 " status: " << it->second.subscribed <<
			 " members: " << it->second.presenceMemberIds.size() <<
			 endl;
	}

	// for (auto it = ChannelData

	//pp.unsubscribe(channel);

	cd = pp.subscriptions();

	cout << "Subs: " << endl;
	for (
		auto it = cd.begin();
		it != cd.end();
		it++
	) {
		cout << "Subscription: " << it->first <<
			 " status: " << it->second.subscribed <<
			 " members: " << it->second.presenceMemberIds.size() <<
			 endl;
	}

	// cout << pp.subscriptions().size() << endl;
}

pushcpp::ChannelAuthentication ch_auth_test(const std::string &socketId, const std::string &channel)
{
	pushcpp::ChannelAuthentication channelAuthentication;
	string postData;
	postData = "{ \"socket_id\": \"" + socketId + "\", " + "\"channel_name\": \"" + channel + "\" }";

	//curl

	//CURL *curl;
	////CURLcode res;
	//struct curl_slist *list = NULL;
	//list = curl_slist_append(list, "Authorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjFiNDA2ZjY0ZTMwNWM3OTI5ODJmYTgxNTk5YzZmZjlhZGI1MzkwMGYwM2EyM2FjMDE3Y2YxNGMwNGE4MzM1MTM5NDRjYTVkYmJhOWFiMTc4In0.eyJhdWQiOiIxIiwianRpIjoiMWI0MDZmNjRlMzA1Yzc5Mjk4MmZhODE1OTljNmZmOWFkYjUzOTAwZjAzYTIzYWMwMTdjZjE0YzA0YTgzMzUxMzk0NGNhNWRiYmE5YWIxNzgiLCJpYXQiOjE1NjQwNTU0MDgsIm5iZiI6MTU2NDA1NTQwOCwiZXhwIjoxNTk1Njc3ODA4LCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.CTDMrSCqpEVWMCyFNBSyQbE_QSRvh8CDO0aBId11pBNWG9jozM9xCyaC3Bdb4LLp6VOVdi_8DeKx4HMcdSy6gwAV10gMfOOJOyixReSH9FOHYorJApzFcQS5xaWgFbh8v7RzxL68ImouSISkxr5yvCnixYDS9nKvG4hX1Dy7vOqJ7aFqBM7iPtfXvFO6TnSxnIMDPEYGbElaqdZ25vH5ZuWS0hpYr5hWaFcrjTZ8Um1inL_9AbJXO2RYcV - PY72VNPFAfOy1GTJvI - WQVmdiLKmd35dWvCNky5C5sw4baVwgRrWeY4Tjt8AG6SExnUj - TaeWiu7hzjxXkZzjKLc9Z9yQbtthQvgozfXjEkgc - e8sipVdhkZQC93FjLHRZIBPUKMDVX2NrmjfVBL3FJvjbW2 - x6nozXvTQnT4gU1BhB_eZrQhZ4s6cS_UN - 9gS3PQLwJmWjY0JlKCKNk2NY4uhWvBnhpJRb2JaLYa7Dk4sIoLwGpiTPc9kp2X4c9WgBfx0BuViL0ZXv3K37j3VQoUcU3fAAXV9RFovb8SGO6oPIuq5XZL - VUbWcDM4PajXpR0bqiaCgmmhw4c0ZR5QpHgrRMQhotpu6SaY3FmQlM2LRwtPzV0IuNxMEcoQhD_i4yEA25ZSq7a25T2jr0lukyH_S1nsVo_rsEIhdZlDlzHSEw");
	//list = curl_slist_append(list, "Accept: application / json");
	//list = curl_slist_append(list, "Content-Type: application/json");
	//curl = curl_easy_init();
	//curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.1.168:81/broadcasting/auth");
	//curl_easy_setopt(curl, CURLOPT_POST, 1);
	//curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
	//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
	//curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, postData.length());
	//curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	//curl_easy_perform(curl);
	//curl_easy_cleanup(curl);
	
	
	//wininet

	HINTERNET hInternet = InternetOpen("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/75.0.3770.142 Safari/537.36",INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);
	HINTERNET hConnect = InternetConnect(hInternet, "192.168.1.168", 81, NULL, NULL, INTERNET_SERVICE_HTTP, NULL, NULL);
	LPCSTR acceptTypes = "*/*";
	LPCSTR rgpszAcceptTypes[] = { "*/*", NULL};
	HINTERNET hRequest = HttpOpenRequest(hConnect, "POST", "broadcasting/auth", NULL, NULL, rgpszAcceptTypes, NULL, NULL);
	LPCSTR lpszHeaders = "Accept: application/json\nContent-Type: application/json\nAuthorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjFiNDA2ZjY0ZTMwNWM3OTI5ODJmYTgxNTk5YzZmZjlhZGI1MzkwMGYwM2EyM2FjMDE3Y2YxNGMwNGE4MzM1MTM5NDRjYTVkYmJhOWFiMTc4In0.eyJhdWQiOiIxIiwianRpIjoiMWI0MDZmNjRlMzA1Yzc5Mjk4MmZhODE1OTljNmZmOWFkYjUzOTAwZjAzYTIzYWMwMTdjZjE0YzA0YTgzMzUxMzk0NGNhNWRiYmE5YWIxNzgiLCJpYXQiOjE1NjQwNTU0MDgsIm5iZiI6MTU2NDA1NTQwOCwiZXhwIjoxNTk1Njc3ODA4LCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.CTDMrSCqpEVWMCyFNBSyQbE_QSRvh8CDO0aBId11pBNWG9jozM9xCyaC3Bdb4LLp6VOVdi_8DeKx4HMcdSy6gwAV10gMfOOJOyixReSH9FOHYorJApzFcQS5xaWgFbh8v7RzxL68ImouSISkxr5yvCnixYDS9nKvG4hX1Dy7vOqJ7aFqBM7iPtfXvFO6TnSxnIMDPEYGbElaqdZ25vH5ZuWS0hpYr5hWaFcrjTZ8Um1inL_9AbJXO2RYcV-PY72VNPFAfOy1GTJvI-WQVmdiLKmd35dWvCNky5C5sw4baVwgRrWeY4Tjt8AG6SExnUj-TaeWiu7hzjxXkZzjKLc9Z9yQbtthQvgozfXjEkgc-e8sipVdhkZQC93FjLHRZIBPUKMDVX2NrmjfVBL3FJvjbW2-x6nozXvTQnT4gU1BhB_eZrQhZ4s6cS_UN-9gS3PQLwJmWjY0JlKCKNk2NY4uhWvBnhpJRb2JaLYa7Dk4sIoLwGpiTPc9kp2X4c9WgBfx0BuViL0ZXv3K37j3VQoUcU3fAAXV9RFovb8SGO6oPIuq5XZL-VUbWcDM4PajXpR0bqiaCgmmhw4c0ZR5QpHgrRMQhotpu6SaY3FmQlM2LRwtPzV0IuNxMEcoQhD_i4yEA25ZSq7a25T2jr0lukyH_S1nsVo_rsEIhdZlDlzHSEw";
	const char* lpszOptional = postData.c_str();
	bool res = HttpSendRequest(hRequest, lpszHeaders, strlen(lpszHeaders), (LPVOID)lpszOptional, postData.length());
	/*char queryInfo[2056];
	DWORD queryInfoLength = strlen(queryInfo);
	DWORD index = 0;
	HttpQueryInfo(hRequest, HTTP_QUERY_RAW_HEADERS_CRLF, queryInfo, &queryInfoLength, &index);
	auto prob = GetLastError();*/
	DWORD bytesRead = 0;
	char httpPostResponse[128];
	res = InternetReadFile(hRequest, httpPostResponse, strlen(httpPostResponse), &bytesRead);

	constexpr char AUTH[] = "auth\":\"";
	char *authStart = strstr(httpPostResponse, AUTH) + strlen(AUTH);
	char *authEnd = strstr(authStart, "\"");
	char authKey[69];
	strncpy(authKey, authStart, authEnd-authStart);
	authKey[68] = '\0';
	channelAuthentication.auth = authKey;
	return channelAuthentication;
}

//size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
//	size_t realsize = size * nmemb;
//	httpPostResponse.append(ptr, realsize);
//	return realsize;
//}

int WINAPI WinMain
(
	HINSTANCE hInstance,		// дескриптор текущего экземпл€ра окна
	HINSTANCE hPrevInstance,		// дескриптор предыдущего экземпл€ра окна 
	LPSTR lpCmdLine,			// указатель на командную строку
	int nCmdShow 			// показывает состо€ние окна 
) {
	WSADATA wsadata;
	WSAStartup(MAKEWORD(1,1),&wsadata);
	pp.connect();
	pp.subscribe("private-user.1", sub_ev, ch_auth_test);
	/*pp.unsubscribe("private-user.1");*/
	pp.join();
	return 0;
}
