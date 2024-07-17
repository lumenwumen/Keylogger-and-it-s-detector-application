# Keylogger-and-it-s-detector-application

KEYLOGGER 

To run the keylogger application execute run.bat file. 
Once the application executes it will hide itself as one of the background processes and start capturing and saving every keyboard input into a .txt file.
The applicatoin will also start a connection with any attacker machine of your choice.
After a given time period the application will then send the .txt file generated to the attacker machine through the connection generated
You can hardcode the ip of attacker machine and time period into the keylogger.exe file 

KEYLOGGER DETECTOR

This application is purely for demonstration purposes as to how the keylogger application can be detected
To initiate it execute the run2.bat file
This application will then look through background processes for a keylogger like application and terminate it once it is found 
It will also look for any suspicious outgoing connections and block it 
