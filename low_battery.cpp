#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <curl/curl.h>
/*
To run this code: g++ low_battery.cpp -o low_battery -lcurl
Ensure to have the curl flag!
*/

/*
 To send the notification using the PUSH BULLET
 @param string API KEY: for Push Bullet
 @param string title: subject of the notification
 @param string body: message to send in the notification
*/
void send_notification(const std::string& API_KEY, const std::string& title, const std::string& body){
    CURL* curl = curl_easy_init();
    if(curl){
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        std::string auth_header = "Access-Token: " + API_KEY;
        
        headers = curl_slist_append(headers, auth_header.c_str());

        std::string post_fields = "{\"type\":\"note\", \"title\":\"" + title + "\", \"body\":\"" + body + "\"}";

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.pushbullet.com/v2/pushes");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());

        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }


}



// Function to check the battery status
void check_battery_status(const std::string& API_KEY){
    std::ifstream charger_file("/sys/class/power_supply/AC/online");
    int charger_status;
    if (charger_file >> charger_status && charger_status == 0){
         std::ifstream battery_file("/sys/class/power_supply/BAT0/capacity");
        int battery_level;
        if(battery_file >> battery_level && battery_level < 20){
            send_notification(API_KEY,  "Low Battery Alert", "Your laptop battery is low. Please plug in the charger.");
        }
    }
   
    

}

// In linux terminal: export PUSH_BULLET_API_KEY=<YOUR_API_KEY>
int main() {
    const char* push_bullet_api_key = std::getenv("PUSH_BULLET_API_KEY");

    if(push_bullet_api_key != nullptr){
        std::string api_key(push_bullet_api_key);
        check_battery_status(push_bullet_api_key);
    } else{
        std::cerr << "API KEY IS NOT SET" << std::endl;
    }

    
    return 0;
}