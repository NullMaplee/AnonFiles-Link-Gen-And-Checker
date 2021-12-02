#include <iostream>
#include <string> 
#include <Windows.h>

#define CURL_STATICLIB

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Wldap32.lib")
#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "Normaliz.lib")

#include "curl/curl.h"

#ifdef _DEBUG
#pragma comment(lib,"libcurl_a_debug.lib")
#else
#pragma comment(lib,"libcurl_a.lib")
#endif

// https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
std::string GenerateRandomString(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

int main()
{
    srand((unsigned)time(NULL));

    std::cout << "AnonFiles Link Generator And Checker" << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;

    CURL* curl = curl_easy_init();
    CURLcode res;

    int Total = 0;
    int Good = 0;
    int Bad = 0;

    while (true)
    {
        std::string Title = "AnonFiles Finder - Total: " + std::to_string(Total) + " Good: " + std::to_string(Good) + " Bad: " + std::to_string(Bad);
        SetConsoleTitleA(Title.c_str());

        std::string CurrentURL = "https://anonfiles.com/" + GenerateRandomString(10);
        curl_easy_setopt(curl, CURLOPT_URL, CurrentURL);
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1); // dont display body of the site
        res = curl_easy_perform(curl);

        long response_code;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);


        if (response_code != 200)
        {
            Bad = Bad + 1;
        }
        else
        {
            Good = Good + 1;
            std::cout << CurrentURL << std::endl;
        }
        Total = Total + 1;
    }

    curl_easy_cleanup(curl);

    system("pause");
}
