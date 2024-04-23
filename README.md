# Low Battery Script  

Currently I have a laptop running Linux Ubuntu which I use as a home server. Since the server is ran on a laptop I do not keep it plugged in all the time to save energy, however this results in, the server shutting down if I forget to plug in the charger.   

Therefore, I wrote a script in C++ to check the battery status of the Linux laptop and send a notification to my phone using Push Bullet.  

* Used C++ for its faster execution, since this script will be set to run automatically every so often.  
* C++ has system level access as such it was easy to access the battery level.  
* Used cURL to interact with the push bullet API, allowing to send a custom subject and message for the notification.  
* Push bullet used to send a notification to my phone and main desktop with ease.  
* Set up a cron job to run the script automatically every 15 minutes.  

## Requirements
**Warning: This script has been tested and used only on Ubuntu. Commands and file paths may differ on other Linux distributions.**  

* C++ installed on the target machine. On Linux Ubuntu can be installed using:
```
sudo apt install g++
```
* cURL installed on the target machine. On Ubuntu it can be installed using:

```
sudo apt install libcurl4-openssl-dev
```
* Push Bullet API key and the app installed on the devices you want to recieve the notification on.  


## How to run it
1. Clone the project or download it.  
2. Ensure to have all the requirements installed.  
3. Open the terminal and create a enviroment varible for the API key using the following command:
    ```
    export PUSH_BULLET_API_KEY=your_api_key_here
    ```
    *Note: There is no need to put quotation marks around the key as it will be converted to a string in the script.*  

    You can confirm the enviorment variable has been created with the command below, it will print the API key to the terminal:
    ```
    echo $PUSH_BULLET_API_KEY
    ```
4. To compile the script into a executable:
    ```
    g++ low_battery.cpp -o low_battery -lcurl
    ```
    *Note: Make sure to put the flag for curl otherwise it will not recongnise the curl commands!*   

    4a. To execute the code, in the main Linux Terminal run it with:
    ```
    ./low_battery
    ``` 
    If the script does not execute then, ensure it has execute permissions using:
    ```
    chmod +x /path/to/your/script
    ```
    *Note: It may not be able to run in the intergated terminal of VS Code due to the enviroment varibles not accessible to it.*  
        
5. To set up a automated cron job:
    5a. In the Linux Terminal, open your crontab file with the following command:
    ```
    crontab -e
    ```
    5b. Edit the file to add your API key:
    ```
    PUSH_BULLET_API_KEY=your_api_key_here
    ```
    *Note: cron may not have access to the enviroment varibles, so if that is the case you can add this line otherwise leave it out.*
    5c. Add the cron job:
    ```
    */15 * * * * /path/to/your/compiled_script
    ```
    *Note: The 15 is the time in minutes specified, when to run the script again.*

    5d. Your crontab file should look like this:
    ```
    # Environment variable
    PUSH_BULLET_API_KEY=your_api_key_here

    # Cron job to run every 15 minutes
    */15 * * * * /path/to/your/compiled_script
    ```
6. You can check if the cron job is being executed by checking the cron log:
    ```
    grep CRON /var/log/syslog
    ```
    You can test the script, by setting the cron job to execute every minute and also changing the condition for battery level to a higher value then the current battery level. If you recieve a notification, then it is working otherwise please ensure you have followed all the steps.  
