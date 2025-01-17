#include "pushcpp_internal.h"

bool pushcpp::subscribe(
	const string &channel,
	const std::string &hostAuthEndpoint,
	const unsigned int &portAuthEndpoint,
	const std::string &pathAuthEndpoint,
	const string &token
)
{
	ChannelData d = m_channelData[channel];

	d.token = token;
	d.hostAuthEndpoint = hostAuthEndpoint;
	d.portAuthEndpoint = portAuthEndpoint;
	d.pathAuthEndpoint = pathAuthEndpoint;

	m_channelData[channel] = d;

	DEBUG("Subscribing to %s", channel.c_str());

	if (connected())
		return sendSubscription(true, channel);
	else
		return false;
}

void pushcpp::unsubscribe(
	const std::string &channel
)
{
	m_channelData.erase(channel);

	DEBUG("Unsubscribing from %s", channel.c_str());

	if (connected())
		sendSubscription(false, channel);
}

std::unordered_map<std::string, pushcpp::ChannelData> pushcpp::subscriptions(
	bool confirmedOnly
) const
{
	unordered_map<string, ChannelData> ret;

	for (
		auto it = m_channelData.begin();
		it != m_channelData.end();
		it++
	)
		if (!confirmedOnly || (confirmedOnly && it->second.subscribed))
			ret[it->first] = it->second;

	return ret;
}

bool pushcpp::sendSubscription(
	bool subscribe,
	const std::string &channel
)
{
	json_t *json = json_object();
	json_object_set_new(
		json, "event",
		json_string(subscribe ? "pusher:subscribe" : "pusher:unsubscribe"));

	json_t *data = json_object();
	json_object_set_new(data, "channel", json_string(channel.c_str()));

	if (subscribe) {
		auto chanData = m_channelData.find(channel);

		if (chanData != m_channelData.end()/* && chanData->second.authHandler != NULL*/) {
			assert(!this->m_socketId.empty());

			ChannelAuthentication authdata =
				this->authHandler(channel, chanData->second.hostAuthEndpoint, chanData->second.portAuthEndpoint, chanData->second.pathAuthEndpoint, chanData->second.token);

			/*	string chdata = authdata.channelData;

			if (chdata == "")
			chdata = "{}";*/

			json_object_set_new(data, "auth",
				json_string(authdata.auth.c_str()));
			/*json_object_set_new(data, "channel_data",
			json_string(chdata.c_str()));*/
		}
	}


	json_object_set_new(json, "data", data);

	char *dumped = json_dumps(json, 0);
	assert(dumped);
	bool ret = sendRaw(dumped);
	free(dumped);
	json_decref(json);
	return ret;
}