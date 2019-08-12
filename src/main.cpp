#include <iostream>
#include <fstream>
#include <curl/curl.h>

static size_t WriteCallBack(void* contents, size_t size, size_t nmemb, void* userp)
{
	static_cast<std::string*>(userp)->append(static_cast<char*>(contents), size * nmemb);

	return size * nmemb;
}

int main(void)
{
	CURL* curl = curl_easy_init();
	CURLcode res;
	std::string readBuffer;

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		res = curl_easy_perform(curl);

		curl_easy_cleanup(curl);

		std::cout << readBuffer.c_str() << std::endl;
	}

	return 0;
}