/* Define Variables and Constants */ 

int Testing =1;
int Pass = 2;
int Fail =3;
int PassFail = Testing;
int Motor = 13;
int PassLight = 10;
int FailLight = 11;
int UnLock = 9;
int Lock = 8;
int Bolt = 7;
int OFF = LOW;
int ON= HIGH;
int Open=HIGH;
int Closed=LOW;
int BoltState=HIGH;                    /* High equals open assume switch is open*/
int LockState=HIGH;                    /* High equals open assume switch is open*/
int UnLockState=HIGH;                  /* High equals open assume switch is open*/
int Time;                         /* time result */
int MaxTime = 5;                    /* 2 seconds Max */
int MinTime = 1;                    /* 1 second min */

/* initialize */

void setup()
{
  pinMode(Motor,OUTPUT);
  digitalWrite(Motor,OFF);            /* start with motor off */
  pinMode(PassLight, OUTPUT);
  digitalWrite(PassLight, OFF);      /* Pass indicator off */
  pinMode(FailLight,OUTPUT);
  digitalWrite(FailLight,OFF);       /* Fail indicator off */
  pinMode(UnLock,INPUT);               /* Open Switch */
  pinMode(Lock, INPUT);              /* Lock Position Switch */
  pinMode(Bolt, INPUT);              /* Bolt Switch */
  
} /* End of Setup */

/*  Main Program Loop */
void loop()                                 /* Main loop */
{
   if(digitalRead(UnLock))                            /* Switch closed ? make sure cam in in the door open position */
  { /* Unlock sw is not clsoed */
    digitalWrite(Motor, ON);                          /* Turn on the motor */
    while(digitalRead(UnLock))                        /* wait until SW closes */
   {
      delay(1);
   } /* end while */
  } /* end if when in open position */
  digitalWrite(Motor,OFF);                          /* stop motor to test switch states */
  CheckState();
  if((BoltState==Closed) || (LockState==Closed))     /* check all switches in correct state */
  {
    PassFail=Fail;                                /* switches not correct set failed flag */
  } /*end if */
  if(PassFail!=Fail)                              /* switchs ok, start test */
  {
    LockLatch();                                  /* start locking sequence */
    CheckState();
    if(BoltState||LockState)                     /* check all switches in locked state */
    {
       PassFail=Fail;                            /* Switches not correct set failed flag */
    } /* End IF */
    if(PassFail!=Fail)                           /* latch is locked */
    {
      if((Time>MaxTime) || (Time<MinTime))       /* check lock time */
      {
        PassFail=Fail;                            /* time to lock either to fast or too slow */
      }/* end if */                               /* validate time to lock */
      if(PassFail!=Fail)
      {
        UlockLatch();
        CheckState();
        if((BoltState==Closed) || (LockState==Closed))
        {
           PassFail=Fail;                                /* switches not correct set failed flag */
        } /*end if */
      } /* end if */   
    }/* END /if */
   }/*END iF */ 
   if(PassFail=Fail)
   {
     digitalWrite(FailLight,ON);
   } /* end if */
   else
   {
     digitalWrite(PassLight, ON);
   } /* end else */
} /* end of testlatch*/

void CheckState()                  /* check state of the open, lock and bolt switch */
{
   BoltState =digitalRead(Bolt);
   LockState=digitalRead(Lock);
  UnLockState=digitalRead(UnLock);
} /* end CheckState */
  
void LockLatch()
{
  Time=0;
  digitalWrite(Motor, ON);
  while(digitalRead(Lock))            /* wait until lock switch closes */
  {
     delay(1);
     Time++;
  } /* end while */
   digitalWrite(Motor,OFF);            /* stop motor to test switch states */
}/* end LockLatch */

void UlockLatch()
{
  Time = 0;
  digitalWrite(Motor, ON);
  while(digitalRead(UnLock))      /* wait until unlock switch closes */
  {
     delay(1);
     Time++;
  } /* end while */
   digitalWrite(Motor,OFF);            /* stop motor to test switch states */
}/* end UlockLatch */


