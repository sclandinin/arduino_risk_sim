/*********************************************************
Risk Battle Simulator
By: Scott Clandinin
June 2016
Micro: ATmega328p-pu

Detailed battle results can be monitored via the serial
monitor at 9600 baud.
**********************************************************/

// I/O
int attacker1 = 8, attacker2 = 7, attacker3 = 6;
int defender1 = 4, defender2 = 3;
int attackDeath1 = 9, attackDeath2 = 11;
int defendDeath1 = 10, defendDeath2 = 12;

//button variables
int sim_button = 13;
int sim_button_state;
int atk_button = 2;
int atk_button_state;
int def_button = 5;
int def_button_state;

//counters - initialized to 3v2
int atk_count = 3;
int def_count = 2;


//***********************************************************************************************
//***********************************************************************************************
void setup() {    
  
  Serial.begin(9600);
  Serial.print("*****Risk Dice Rolling Simulator*****\n\r\n\r");
  
  // initialize the digital pins
  pinMode(attacker1, OUTPUT); 
  pinMode(attacker2, OUTPUT);   
  pinMode(attacker3, OUTPUT);   
  pinMode(defender1, OUTPUT);   
  pinMode(defender2, OUTPUT);
  pinMode(attackDeath1, OUTPUT);   
  pinMode(attackDeath2, OUTPUT);
  pinMode(defendDeath1, OUTPUT);   
  pinMode(defendDeath2, OUTPUT);
  
  pinMode(sim_button, INPUT);
  pinMode(atk_button, INPUT);
  pinMode(def_button, INPUT);
  
  digitalWrite(attacker1, HIGH);   
  digitalWrite(attacker2, HIGH);  
  digitalWrite(attacker3, HIGH);   
  digitalWrite(defender1, HIGH);   
  digitalWrite(defender2, HIGH);   
}

//***********************************************************************************************
//***********************************************************************************************
void loop() {

  //increment atk counter
  atk_button_state = digitalRead(atk_button);  
  if (atk_button_state)
  {
    atk_count = atk_count + 1;
    
    if (atk_count == 4)
    {
      atk_count = 1; 
    }
    
    switch(atk_count)   //case value represents number of attackers
    {
    case 1:
      digitalWrite(attacker1, HIGH);   
      digitalWrite(attacker2, LOW);   
      digitalWrite(attacker3, LOW); 
      delay(250);  //wait for switch bouncing  
      break;
	
    case 2:
      digitalWrite(attacker1, HIGH);   
      digitalWrite(attacker2, HIGH);   
      digitalWrite(attacker3, LOW);  
      delay(250);  //wait for switch bouncing  
      break;
  
    case 3:
      digitalWrite(attacker1, HIGH);   
      digitalWrite(attacker2, HIGH);  
      digitalWrite(attacker3, HIGH);  
      delay(250);  //wait for switch bouncing  
      break;   
    }
  }
  
  
  //increment def counter
  def_button_state = digitalRead(def_button);  
  if (def_button_state)
  {
    def_count = def_count + 1;
    
    if (def_count == 3)
    {
      def_count = 1; 
    }
    
    switch(def_count)   //case value represents number of defenders
    {
    case 1:
      digitalWrite(defender1, HIGH);   
      digitalWrite(defender2, LOW);  
      delay(250);  //wait for switch bouncing      
      break;
	
    case 2:
      digitalWrite(defender1, HIGH);   
      digitalWrite(defender2, HIGH);  
      delay(250);  //wait for switch bouncing     
      break;
    }
  }
  
  //simulate the battle based on number of attackers and defenders
  sim_button_state = digitalRead(sim_button);  
  if (sim_button_state)
  {
    thinking();
    if (atk_count == 3 && def_count == 2)
    {
      simulate_3v2();
    }
    else if (atk_count == 3 && def_count == 1)
    {
      simulate_3v1();
    }
    else if (atk_count == 2 && def_count == 2)
    {
      simulate_2v2();
    }
    else if (atk_count == 2 && def_count == 1)
    {
      simulate_2v1();
    }
    else if (atk_count == 1 && def_count == 2)
    {
      simulate_1v2();
    }
    else if (atk_count == 1 && def_count == 1)
    {
      simulate_1v1();
    }
    
  }

}

//***********************************************************************************************
//***********************************************************************************************
//LED display to indicate simulation is underway
void thinking()
{
  for (int i = 0; i < 3; i++)
  {
  digitalWrite(attackDeath1, LOW);  
  digitalWrite(defendDeath1, LOW); 
  digitalWrite(attackDeath2, LOW);  
  digitalWrite(defendDeath2, LOW);    
  delay(100);               // wait
  digitalWrite(attackDeath1, HIGH);  
  digitalWrite(defendDeath1, HIGH);   
  digitalWrite(attackDeath2, HIGH);   
  digitalWrite(defendDeath2, HIGH);    
  delay(100);               // wait
  digitalWrite(attackDeath1, LOW);   
  digitalWrite(defendDeath1, LOW);   
  digitalWrite(attackDeath2, LOW);  
  digitalWrite(defendDeath2, LOW);   
  delay(100);               // wait 
  }
}

//***********************************************************************************************
//***********************************************************************************************
//simulate the 3v2 battle
void simulate_3v2()
{
  int a[3];
  int d[2];
  int buffer = 0;
  
  a[0] = random(1,7);
  a[1] = random(1,7);
  a[2] = random(1,7);
  d[0] = random(1,7);
  d[1] = random(1,7);

  
  //sort attacker dice *****************
  //bubble sort largest to smallest
  for (int i = 0; i<3; i++)	
  {
	for (int j = 0; j < 2; j++)
	{
	  if (a[j] < a[j+1])
	  {
	    buffer = a[j];
	    a[j] = a[j+1];
	    a[j+1] = buffer;
	   }
	}
  }
  
  //sort defender dice from largest to smallest
  if (d[1] > d[0])
  {
    buffer = d[0];
    d[0] = d[1];
    d[1] = buffer;
  }
  
  //display results on serial monitor
  Serial.print("*********************\n\r");
  Serial.print("Results 3v2:\n\r\n\r");
  Serial.print("Attacker Dice:\n\r");
  Serial.print(a[0]);
  Serial.print(a[1]);
  Serial.print(a[2]);
  Serial.print("\n\r");
  Serial.print("Defender Dice:\n\r");
  Serial.print(d[0]);
  Serial.print(d[1]);
  Serial.print("\n\r");
  Serial.print("*********************\n\r\n\r");

  //test the top dice of each
  if (d[0] >= a[0])
  {
     digitalWrite(attackDeath1, HIGH);   
     digitalWrite(defendDeath1, LOW);   
  }
  else
  {
     digitalWrite(attackDeath1, LOW);  
     digitalWrite(defendDeath1, HIGH);    
  }
  
  //test the next highest dice of each
    if (d[1] >= a[1])
  {
     digitalWrite(attackDeath2, HIGH);  
     digitalWrite(defendDeath2, LOW);   
  }
  else
  {
     digitalWrite(attackDeath2, LOW);
     digitalWrite(defendDeath2, HIGH);
  }
}
//***********************************************************************************************
//***********************************************************************************************



//***********************************************************************************************
//***********************************************************************************************
//simulate the 3v1 battle
void simulate_3v1()
{
  int a[3];
  int d[1];
  int buffer = 0;
  
  a[0] = random(1,7);
  a[1] = random(1,7);
  a[2] = random(1,7);
  d[0] = random(1,7);

  
  //sort attacker dice *****************
  //bubble sort largest to smallest
  for (int i = 0; i<3; i++)	
  {
	for (int j = 0; j < 2; j++)
	{
	  if (a[j] < a[j+1])
	  {
	    buffer = a[j];
	    a[j] = a[j+1];
	    a[j+1] = buffer;
	   }
	}
  }
  
  
  //display results on serial monitor
  Serial.print("*********************\n\r");
  Serial.print("Results 3v1:\n\r\n\r");
  Serial.print("Attacker Dice:\n\r");
  Serial.print(a[0]);
  Serial.print(a[1]);
  Serial.print(a[2]);
  Serial.print("\n\r");
  Serial.print("Defender Dice:\n\r");
  Serial.print(d[0]);
  Serial.print("\n\r");
  Serial.print("*********************\n\r\n\r");

  //test the top dice of each
  if (d[0] >= a[0])
  {
     digitalWrite(attackDeath1, HIGH);   
     digitalWrite(defendDeath1, LOW);   
  }
  else
  {
     digitalWrite(attackDeath1, LOW);  
     digitalWrite(defendDeath1, HIGH);    
  }
  
}
//***********************************************************************************************
//***********************************************************************************************

//***********************************************************************************************
//***********************************************************************************************
//simulate the 2v2 battle
void simulate_2v2()
{
  int a[3];
  int d[2];
  int buffer = 0;
  
  a[0] = random(1,7);
  a[1] = random(1,7);
  d[0] = random(1,7);
  d[1] = random(1,7);
  
  //sort attacker dice *****************
  if (a[1] > a[0])
  {
    buffer = a[0];
    a[0] = a[1];
    a[1] = buffer;
  }
  
  //sort defender dice from largest to smallest
  if (d[1] > d[0])
  {
    buffer = d[0];
    d[0] = d[1];
    d[1] = buffer;
  }
  
  //display results on serial monitor
  Serial.print("*********************\n\r");
  Serial.print("Results 2v2:\n\r\n\r");
  Serial.print("Attacker Dice:\n\r");
  Serial.print(a[0]);
  Serial.print(a[1]);
  Serial.print("\n\r");
  Serial.print("Defender Dice:\n\r");
  Serial.print(d[0]);
  Serial.print(d[1]);
  Serial.print("\n\r");
  Serial.print("*********************\n\r\n\r");

  //test the top dice of each
  if (d[0] >= a[0])
  {
     digitalWrite(attackDeath1, HIGH);   
     digitalWrite(defendDeath1, LOW);   
  }
  else
  {
     digitalWrite(attackDeath1, LOW);  
     digitalWrite(defendDeath1, HIGH);    
  }
  
  //test the next highest dice of each
    if (d[1] >= a[1])
  {
     digitalWrite(attackDeath2, HIGH);  
     digitalWrite(defendDeath2, LOW);   
  }
  else
  {
     digitalWrite(attackDeath2, LOW);
     digitalWrite(defendDeath2, HIGH);
  }
}
//***********************************************************************************************
//***********************************************************************************************

//***********************************************************************************************
//***********************************************************************************************
//simulate the 2v1 battle
void simulate_2v1()
{
  int a[3];
  int d[2];
  int buffer = 0;
  
  a[0] = random(1,7);
  a[1] = random(1,7);
  d[0] = random(1,7);

  
  //sort attacker dice *****************
  if (a[1] > a[0])
  {
    buffer = a[0];
    a[0] = a[1];
    a[1] = buffer;
  }
  
  //display results on serial monitor
  Serial.print("*********************\n\r");
  Serial.print("Results 2v1:\n\r\n\r");
  Serial.print("Attacker Dice:\n\r");
  Serial.print(a[0]);
  Serial.print(a[1]);
  Serial.print("\n\r");
  Serial.print("Defender Dice:\n\r");
  Serial.print(d[0]);
  Serial.print("\n\r");
  Serial.print("*********************\n\r\n\r");

  //test the top dice of each
  if (d[0] >= a[0])
  {
     digitalWrite(attackDeath1, HIGH);   
     digitalWrite(defendDeath1, LOW);   
  }
  else
  {
     digitalWrite(attackDeath1, LOW);  
     digitalWrite(defendDeath1, HIGH);    
  }
  
}
//***********************************************************************************************
//***********************************************************************************************

//***********************************************************************************************
//***********************************************************************************************
//simulate the 1v2 battle
void simulate_1v2()
{
  int a[3];
  int d[2];
  int buffer = 0;
  
  a[0] = random(1,7);
  d[0] = random(1,7);
  d[1] = random(1,7);
  
  
  //sort defender dice from largest to smallest
  if (d[1] > d[0])
  {
    buffer = d[0];
    d[0] = d[1];
    d[1] = buffer;
  }
  
  //display results on serial monitor
  Serial.print("*********************\n\r");
  Serial.print("Results 1v2:\n\r\n\r");
  Serial.print("Attacker Dice:\n\r");
  Serial.print(a[0]);
  Serial.print("\n\r");
  Serial.print("Defender Dice:\n\r");
  Serial.print(d[0]);
  Serial.print(d[1]);
  Serial.print("\n\r");
  Serial.print("*********************\n\r\n\r");

  //test the top dice of each
  if (d[0] >= a[0])
  {
     digitalWrite(attackDeath1, HIGH);   
     digitalWrite(defendDeath1, LOW);   
  }
  else
  {
     digitalWrite(attackDeath1, LOW);  
     digitalWrite(defendDeath1, HIGH);    
  }
  
}
//***********************************************************************************************
//***********************************************************************************************

//***********************************************************************************************
//***********************************************************************************************
//simulate the 1v1 battle
void simulate_1v1()
{
  int a[3];
  int d[2];
  int buffer = 0;
  
  a[0] = random(1,7);
  d[0] = random(1,7);

  //display results on serial monitor
  Serial.print("*********************\n\r");
  Serial.print("Results 1v1:\n\r\n\r");
  Serial.print("Attacker Dice:\n\r");
  Serial.print(a[0]);
  Serial.print("\n\r");
  Serial.print("Defender Dice:\n\r");
  Serial.print(d[0]);
  Serial.print("\n\r");
  Serial.print("*********************\n\r\n\r");

  //test the top dice of each
  if (d[0] >= a[0])
  {
     digitalWrite(attackDeath1, HIGH);   
     digitalWrite(defendDeath1, LOW);   
  }
  else
  {
     digitalWrite(attackDeath1, LOW);  
     digitalWrite(defendDeath1, HIGH);    
  }
  
}
//***********************************************************************************************
//***********************************************************************************************
