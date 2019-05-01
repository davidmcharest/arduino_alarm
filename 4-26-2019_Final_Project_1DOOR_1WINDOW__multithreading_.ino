
  //Not Verified!!!!
  //How it Works:
  //alarm() function is run initially and checks to see if alarmActivated = true and AWAYalarmActivated (they start as false), then loops
  //to the mainMenu() function. The mainMenu() function checks if activateAlarm or AWAYactivateAlarm = true. If either is true,  the countdown will display and 
  //
  //
  //

  #include <LiquidCrystal.h> // includes the LiquidCrystal Library 
  #include <Keypad.h>        // includes the Keypad Library

  //Assigning pin numbers to lasers
  int LaserEmitterW = 11; 
  int LaserEmitterP = 13;

  //Assigning pin numbers to receivers
  int LaserDetectorW = 10;
  int LaserDetectorP = 12;

  //Assigning pin number to piezo buzzer
  int Buzzer = 46;


  int screenOffMsg =0; // Used in mainMenu and enterPassword functions. If value is 0, display Welcome menu text and input options
  String password="1234"; // Used in enterPassword function as the current password to disable alarm or change password
  String tempPassword; // Used in enterPassword function to store keys to compare to String password
  boolean activated = false; // Used in enterPassword function to determine if keys should be pressed
  boolean isActivated; // from borrowed code to check to see if alarm is activated. Currently not in use
  boolean activateAlarm = false; // Used in mainMenu function to check to see if alarm is activated and provide a countdown
  boolean AWAYactivateAlarm = false; // Used in mainMenu function to check to see if alarm is activated and provide a countdown
  boolean alarmActivated = false; // Used in alarm and enterPassword functions to only run alarm function if this is equal to true
  boolean AWAYalarmActivated = false; // Used in alarm and enterPassword functions to only run alarm function if this is equal to true
  boolean enteredPassword; // State of the entered password to stop the alarm
  boolean passChangeMode = false; // Used in enterPassword function
  boolean passChanged = false; // Used in enterPassword function
  const byte ROWS = 4; //four rows
  const byte COLS = 4; //four columns
  char keypressed;

  //define the symbols on the buttons of the keypads
  char keyMap[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
  };
  byte rowPins[ROWS] = {18, 19, 20, 21}; //Row pinouts of the keypad
  byte colPins[COLS] = {14, 15, 16, 17}; //Column pinouts of the keypad
  Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, ROWS, COLS); 
  LiquidCrystal lcd(8,9,4,5,6,7); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
  void setup() { 
    lcd.begin(20,4); //defines dimensions of lcd (20 columns by 4 rows)
    Serial.begin (9600);

  //Defines lasers and buzzer as outputs and receivers as inputs
  pinMode(LaserEmitterW, OUTPUT);
  pinMode(LaserDetectorW, INPUT);
  pinMode(LaserEmitterP, OUTPUT);
  pinMode(LaserDetectorP, INPUT);
  pinMode(Buzzer, OUTPUT);
  }
   //########################################################################
   //###################### FUNCTION DEFINITIONS START ######################
   //########################################################################
  void alarm();
  void enterPassword();
  void AWAYenterPassword();
  void ARMEDenterPassword();
  void mainMenu();
   //########################################################################
   //###################### FUNCTION DEFINITIONS END ########################
   //########################################################################
  void loop() { //start of the loop

  //Turns on lasers
  digitalWrite(LaserEmitterW, HIGH);
  digitalWrite(LaserEmitterP, HIGH);

  //sets receiver values
  boolean W = digitalRead(LaserDetectorW);
  boolean P = digitalRead(LaserDetectorP);

  Serial.println(W); // Open the Serial Monitor to see the values
  Serial.println(P); // Open the Serial Monitor to see the values

  alarm();    //calls the alarm function
  mainMenu(); //calls the mainMenu function
  } //end of the loop
   //########################################################################
   //############################ FUNCTIONS #################################
   //########################################################################
  void alarm() { //checks to see if the alarm is currently set to active. If it is, check to see if any lasers are tripped. If a laser is tripped, display a message and turn on the buzzer, then call the enterPassword function

  boolean W = digitalRead(LaserDetectorW);
  boolean P = digitalRead(LaserDetectorP);

    if (alarmActivated == true){
      if (W == 1 && P == 1) 
  {
  //lcd.clear();
  lcd.setCursor(0,2);
    lcd.print("                    ");
    lcd.setCursor(0,3);
    lcd.print("                    ");
  lcd.setCursor(0,2);
  //text to print
  lcd.print("Window     - Armed");
  lcd.setCursor(0,3);
  lcd.print("Front Door - Armed");
  //digitalWrite(Buzzer, LOW);
   delay(2000);
  ARMEDenterPassword(); 
  //lcd.clear();
  }
  else
  {
    if (W == 0 && P == 0)
    {
    
  lcd.setCursor(0,2);
  //text to print
  lcd.print("Window     - ALERT!");
  lcd.setCursor(0,3);
  lcd.print("Front Door - ALERT!");
  digitalWrite(Buzzer, HIGH);
  enterPassword(); //calls the enterPassword function
    }
  else 
  {
     if (W == 1 && P == 0)
     {
  lcd.setCursor(0,2);
  //text to print
  lcd.print("Window     - Armed");
  lcd.setCursor(0,3);
  lcd.print("Front Door - ALERT!");
  digitalWrite(Buzzer, HIGH);
      enterPassword(); //calls the enterPassword function
  }
  else 
  {
     if (W == 0 && P == 1)
     {
  lcd.setCursor(0,2);
  //text to print
  lcd.print("Window     - ALERT!");
  lcd.setCursor(0,3);
  lcd.print("Front Door - Armed");
  digitalWrite(Buzzer, HIGH);
      enterPassword(); //calls the enterPassword function
  }
  else 
  {
  lcd.setCursor(0,2);
  //text to print
  lcd.print(" Error ");
  lcd.setCursor(0,3);
  lcd.print("With Loops");
  digitalWrite(Buzzer, HIGH);
      enterPassword(); //calls the enterPassword function
  }}}}}
    if (AWAYalarmActivated == true){
   if (W == 1 && P == 1) 
  {
  lcd.clear();
  lcd.setCursor(0,2);
  //text to print
  lcd.print("Window     - Armed");
  lcd.setCursor(0,3);
  lcd.print("Front Door - Armed");
  //digitalWrite(Buzzer, LOW);
   delay(2000); 
   ARMEDenterPassword(); 
  }
  else
  {
    if (W == 0 && P == 0)
    {
    
  lcd.setCursor(0,2);
  //text to print
  lcd.print("Window     - ALERT!");
  lcd.setCursor(0,3);
  lcd.print("Front Door - ALERT!");

  delay(1000);
  //lcd.clear();
      AWAYenterPassword(); //calls the AWAYenterPassword function
    }
  else 
  {
     if (W == 1 && P == 0)
     {
  lcd.setCursor(0,2);
  //text to print
  lcd.print("Window     - Armed");
  lcd.setCursor(0,3);
  lcd.print("Front Door - ALERT!");
  //digitalWrite(Buzzer, HIGH);
   delay(2000); 
  //lcd.clear();
      AWAYenterPassword(); //calls the AWAYenterPassword function
  }
  else 
  {
     if (W == 0 && P == 1)
     {
  lcd.setCursor(0,2);
  //text to print
  lcd.print("Window     - ALERT!");
  lcd.setCursor(0,3);
  lcd.print("Front Door - Armed");
  //digitalWrite(Buzzer, HIGH);
   delay(2000); 
  //lcd.clear();
      AWAYenterPassword(); //calls the AWAYenterPassword function
  }
  else 
  {
  lcd.setCursor(0,2);
  //text to print
  lcd.print(" Error ");
  lcd.setCursor(0,3);
  lcd.print("With Loops");
  //digitalWrite(Buzzer, HIGH);
   delay(2000); 
  //lcd.clear();
      AWAYenterPassword(); //calls the AWAYenterPassword function
  }}}}}
  }
  void enterPassword() { //activates keypad and waits for input from user. If entered, turn off alarm 
    int k=5;
    tempPassword = "";
    activated = true;
    //lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("                    ");
    lcd.setCursor(0,1);
    lcd.print("                    ");
    lcd.setCursor(0,0);
    lcd.print(" *** ALARM *** ");
    lcd.setCursor(0,1);
    lcd.print("Pass>");
      while(activated) {
      keypressed = myKeypad.getKey();
      if (keypressed != NO_KEY){
        if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
        keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
        keypressed == '8' || keypressed == '9' )  {
        tempPassword += keypressed;
        lcd.setCursor(k,1);
        lcd.print("*");
        k++;
        }
      }
      if (k > 9 || keypressed == '#') {
      tempPassword = "";
      k=5;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" *** ALARM *** ");
      lcd.setCursor(0,1);
      lcd.print("Pass>");
      }
      if (keypressed == '*') {
      if (tempPassword == password ) {
        activated = false;
        alarmActivated = false;
      digitalWrite(Buzzer, LOW);
        screenOffMsg = 0; 
      }
      else if (tempPassword != password) {
        lcd.setCursor(0,1);
        lcd.print("Wrong! Try Again");
        delay(2000); //wrong pw
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" *** ALARM *** ");
        lcd.setCursor(0,1);
        lcd.print("Pass>");
      }
      }    
            }
  }
  void AWAYenterPassword() { //activates keypad and waits for input from user. If entered, turn off alarm. This function needs to display a 30 second countdown in rows 1 and 2 of the lcd while allowing
                 //user the input the password in the keypad to turn off the system before the buzzer goes off 
    int k=5;
    tempPassword = "";
    activated = true;
    //lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("                    ");
    lcd.setCursor(0,1);
    lcd.print("                    ");
    lcd.setCursor(0,0);
    lcd.print(" *** ALARM *** ");
    lcd.setCursor(0,1);
    lcd.print("Pass>");
      while(activated) {
          if (activated == true) {
      lcd.setCursor(0,1);
    lcd.print("Alarm engaged in");
       int countdown = 30; // 30 seconds count down before activating the alarm
    while (countdown != 0) {
      lcd.setCursor(18,1);
      lcd.print(countdown);
      countdown--;
      delay(1000);
      lcd.setCursor(18,1);
      lcd.print("  ");
    }
    digitalWrite(Buzzer, HIGH);
      keypressed = myKeypad.getKey();
      if (keypressed != NO_KEY){
        if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
        keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
        keypressed == '8' || keypressed == '9' )  {
        tempPassword += keypressed;
        lcd.setCursor(k,1);
        lcd.print("*");
        k++;
        }
      }
      if (k > 9 || keypressed == '#') {
      tempPassword = "";
      k=5;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" *** ALARM *** ");
      lcd.setCursor(0,1);
      lcd.print("Pass>");
      }
      if (keypressed == '*') {
      if (tempPassword == password ) {
        activated = false;
        AWAYalarmActivated = false;
      digitalWrite(Buzzer, LOW);
        screenOffMsg = 0; 
      }
      else if (tempPassword != password) {
        lcd.setCursor(0,1);
        lcd.print("Wrong! Try Again");
        delay(2000); //wrong pw
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" *** ALARM *** ");
        lcd.setCursor(0,1);
        lcd.print("Pass>");
      }
      }    
            }
  }
  }
  void ARMEDenterPassword() { //activates keypad and waits for input from user. If entered, turn off alarm 
    int k=5;
    tempPassword = "";
    activated = true;
    //lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("                    ");
    lcd.setCursor(0,1);
    lcd.print("                    ");
    lcd.setCursor(0,0);
    lcd.print("Type PW to disable");
    lcd.setCursor(0,1);
    lcd.print("Pass>");
      while(activated) {
      keypressed = myKeypad.getKey();
      if (keypressed != NO_KEY){
        if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
        keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
        keypressed == '8' || keypressed == '9' )  {
        tempPassword += keypressed;
        lcd.setCursor(k,1);
        lcd.print("*");
        k++;
        }
      }
      if (k > 9 || keypressed == '#') {
      tempPassword = "";
      k=5;
      //lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("                    ");
    lcd.setCursor(0,1);
    lcd.print("                    ");
      lcd.setCursor(0,0);
      lcd.print("Type PW to disable");
      lcd.setCursor(0,1);
      lcd.print("Pass>");
      }
      if (keypressed == '*') {
      if (tempPassword == password ) {
        activated = false;
        alarmActivated = false;
        AWAYalarmActivated = false;
      digitalWrite(Buzzer, LOW);
        screenOffMsg = 0; 
      }
      else if (tempPassword != password) {
        lcd.setCursor(0,1);
        lcd.print("Wrong! Try Again");
        delay(2000); //wrong pw
    lcd.setCursor(0,0);
    lcd.print("                    ");
    lcd.setCursor(0,1);
    lcd.print("                    ");
        lcd.setCursor(0,0);
        lcd.print("Type PW to disable");
        lcd.setCursor(0,1);
        lcd.print("Pass>");
      }
      }    
            }
  }
  void mainMenu() { //if alarm is active, displays a countdown. If alarm is not active, display welcome menu
      if (activateAlarm) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Alarm will be");
    lcd.setCursor(0,1);
    lcd.print("activated in");
     
    int countdown = 3; // 3 seconds count down before activating the alarm
    while (countdown != 0) {
      lcd.setCursor(13,1);
      lcd.print(countdown);
      countdown--;
      delay(1000);
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Alarm Activated!");
    activateAlarm = false;
    alarmActivated = true;
    }
      if (AWAYactivateAlarm) {
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Alarm will be");
    lcd.setCursor(0,1);
    lcd.print("activated in");
     
    int countdown = 10; // 10 seconds count down before activating the alarm
    while (countdown != 0) {
      lcd.setCursor(14,1);
      lcd.print(countdown);
      countdown--;
      delay(1000);
      lcd.setCursor(14,1);
      lcd.print("  ");
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Alarm Activated!");
    AWAYactivateAlarm = false;
    AWAYalarmActivated = true;
    }
    if (!alarmActivated && !AWAYalarmActivated) {
    
    if (screenOffMsg == 0){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("***** Welcome *****");
      lcd.setCursor(0,1);
      lcd.print("A - Activate Away");
      lcd.setCursor(0,2);
      lcd.print("B - Activate Stay");
      lcd.setCursor(0,3);
      lcd.print("C - Change Password");
      screenOffMsg = 1;
    }
    keypressed = myKeypad.getKey();
     if (keypressed =='A'){      //If A is pressed, activate the AWAY alarm
      AWAYactivateAlarm = true;           
    }
    else if (keypressed =='B'){  //If B is pressed, activate the STAY alarm
      activateAlarm = true;           
    }
    else if (keypressed =='C'){  //If C is pressed, activate keypad and ask for current password, then new password if current correct
      lcd.clear();
      int i=1;
      tempPassword = "";
      lcd.setCursor(0,0);
      lcd.print("Current Password");
      lcd.setCursor(0,1);
      lcd.print(">");
      passChangeMode = true;
      passChanged = true;   
      while(passChanged) {      
      keypressed = myKeypad.getKey();
      if (keypressed != NO_KEY){
      if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
        keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
        keypressed == '8' || keypressed == '9' ) {
       tempPassword += keypressed;
       lcd.setCursor(i,1);
       lcd.print("*");
       i++;
      }
      }
      if (i > 5 || keypressed == '#') {
      tempPassword = "";
      i=1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Current Password");
      lcd.setCursor(0,1);
      lcd.print(">"); 
      }
      if ( keypressed == '*') {
      i=1;
      if (password == tempPassword) {
        tempPassword="";
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Set New Password");
        lcd.setCursor(0,1);
        lcd.print(">");
        while(passChangeMode) {
        keypressed = myKeypad.getKey();
        if (keypressed != NO_KEY){
          if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
            keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
            keypressed == '8' || keypressed == '9' ) {
          tempPassword += keypressed;
          lcd.setCursor(i,1);
          lcd.print("*");
          i++;
          }
        }
        if (i > 5 || keypressed == '#') {
          tempPassword = "";
          i=1;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Set New Password");
          lcd.setCursor(0,1);
          lcd.print(">");
        }
        if (keypressed == '*') {
          i=1;
          password = tempPassword;
          passChangeMode = false;
          passChanged = false;
          screenOffMsg = 0;
        }            
        }
      }
          else if (tempPassword != password) {
        lcd.setCursor(0,0);
        lcd.print("Wrong! Try Again");
        tempPassword = "";
        i=1;
        delay(2000); //current pw
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Current Password");
        lcd.setCursor(0,1);
        lcd.print(">");}
      }
    }
     }
    }
  }
