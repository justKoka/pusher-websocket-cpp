#include "pushcpp_internal.h"

bool pushcpp::subscribe(
	const string &channel,
	ChannelEventHandler event,
	ChannelAuthHandler auth,
	const string &token
)
{
	ChannelData d = m_channelData[channel];

	if (event != NULL)
		d.eventHandlers.insert(event);

	if (auth != NULL)
		d.authHandler = auth;
	else
		d.authHandler = NULL;

	d.token = token;

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

		if (chanData != m_channelData.end() && chanData->second.authHandler != NULL) {
			assert(!this->m_socketId.empty());

			//std::string token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjFiNDA2ZjY0ZTMwNWM3OTI5ODJmYTgxNTk5YzZmZjlhZGI1MzkwMGYwM2EyM2FjMDE3Y2YxNGMwNGE4MzM1MTM5NDRjYTVkYmJhOWFiMTc4In0.eyJhdWQiOiIxIiwianRpIjoiMWI0MDZmNjRlMzA1Yzc5Mjk4MmZhODE1OTljNmZmOWFkYjUzOTAwZjAzYTIzYWMwMTdjZjE0YzA0YTgzMzUxMzk0NGNhNWRiYmE5YWIxNzgiLCJpYXQiOjE1NjQwNTU0MDgsIm5iZiI6MTU2NDA1NTQwOCwiZXhwIjoxNTk1Njc3ODA4LCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.CTDMrSCqpEVWMCyFNBSyQbE_QSRvh8CDO0aBId11pBNWG9jozM9xCyaC3Bdb4LLp6VOVdi_8DeKx4HMcdSy6gwAV10gMfOOJOyixReSH9FOHYorJApzFcQS5xaWgFbh8v7RzxL68ImouSISkxr5yvCnixYDS9nKvG4hX1Dy7vOqJ7aFqBM7iPtfXvFO6TnSxnIMDPEYGbElaqdZ25vH5ZuWS0hpYr5hWaFcrjTZ8Um1inL_9AbJXO2RYcV-PY72VNPFAfOy1GTJvI-WQVmdiLKmd35dWvCNky5C5sw4baVwgRrWeY4Tjt8AG6SExnUj-TaeWiu7hzjxXkZzjKLc9Z9yQbtthQvgozfXjEkgc-e8sipVdhkZQC93FjLHRZIBPUKMDVX2NrmjfVBL3FJvjbW2-x6nozXvTQnT4gU1BhB_eZrQhZ4s6cS_UN-9gS3PQLwJmWjY0JlKCKNk2NY4uhWvBnhpJRb2JaLYa7Dk4sIoLwGpiTPc9kp2X4c9WgBfx0BuViL0ZXv3K37j3VQoUcU3fAAXV9RFovb8SGO6oPIuq5XZL-VUbWcDM4PajXpR0bqiaCgmmhw4c0ZR5QpHgrRMQhotpu6SaY3FmQlM2LRwtPzV0IuNxMEcoQhD_i4yEA25ZSq7a25T2jr0lukyH_S1nsVo_rsEIhdZlDlzHSEw";

			ChannelAuthentication authdata =
				chanData->second.authHandler(this->m_socketId, channel, chanData->second.token);

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