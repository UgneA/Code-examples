using namespace std;

#include <iostream>
#include <iomanip>
#include "Time.h"

/*constructor that initialises all values to zero*/
Time::Time()
{ hour = min = sec = 0;
}

/* constructor that initialises values to those provided by user*/
Time::Time(int h, int m, int s)
{ setTime(h, m, s);
}

/*checks whether provided values for time object are 
valid and sets values accordingly*/
void Time::setTime(int h, int m, int s)
{ hour = (h>=0 && h<24) ? h : 0;
  min = (m>=0 && m<60) ? m : 0;
  sec = (s>=0 && s<60) ? s : 0;
}

/*increments time object's value by provided number of seconds
and assigns it to the variable the operator was applied to*/
Time& Time::operator+=(unsigned int n)
{ sec += n;
  if (sec >= 60)
  { min += sec/60;
    sec %= 60;
    if (min >=60)
    { hour = (hour + min/60) % 24;
      min %= 60;
    }
  }
  return *this;
}
/*increments time value by provided number of seconds*/
Time Time::operator+(unsigned int n) const
{ Time tCopy(*this);
  tCopy += n;
  return tCopy;
}

//increments object's value by one and returns the incremented value
Time& Time::operator++()        // prefix version
{ *this += 1;
  return *this;
}

/*increments object's value by one and returns
 the old (non incremented) value*/
Time Time::operator++(int n)    // postfix version
{ Time tCopy(*this);
  *this += 1;
  return tCopy;
}

/*outputs time objects in the form of hh:mm:ss */
ostream& operator<<(ostream &o, const Time &t)
{ o << setfill('0') << setw(2) <<  t.hour << ':' << setw(2) << t.min << ':' << setw(2) << t.sec;
  return o;
}

/*decrements time object's value by provided number of seconds
and assigns it to the variable the operator was applied to*/
Time& Time::operator-=(unsigned int n)
{ if (sec >= n)
    {
     sec -= n;
    }

  else
   {
    Time t(*this);
    int curTime = t.hour * 60 * 60 + t.min * 60 + t.sec;

    n = n%86400;

    if(curTime >= n ) // if current time is equal to more seconds than the amount of seconds provided as an argument
    { curTime -= n ;
      hour = curTime/3600;
      min = (curTime%3600)/60;
      sec = curTime%60;
    }
    else								// if current time's amount of seconds is lesser than the amount provided as argument
    { curTime = (curTime + 86400 - n);  // add one day's  worth of seconds and then decrement the provided seconds
      hour = curTime/3600;
      min = (curTime%3600)/60;
      sec = curTime%60;
    }
   }
    return *this;
  }
  
/*checks whether two time objects are equal*/
bool Time::operator==(const Time& t) const
{
  Time tCopy(*this);
// converts values of time objects into seconds
  int h1 = tCopy.hour * 60 * 60;
  int m1 = tCopy.min * 60;
  int s1 = tCopy.sec;

  int h2 = t.hour * 60 *60;
  int m2 = t.min * 60;
  int s2 = t.sec;

  if(h1==h2 && m1==m2 && s1==s2)
    return true;

  return false;
}

/*checks whether left-hand side time value is smaller(occurrs
 earlier in the day) than the one on the right-hand side*/
bool Time::operator<(const Time& t) const
{
  Time tCopy(*this);

  int sum1 =tCopy.hour * 60 * 60 + tCopy.min * 60 + tCopy.sec;
  int sum2 =t.hour * 60 * 60 + t.min * 60 + t.sec;

  if(sum1<sum2)
    return true;

  return false;
}

/*checks whether left-hand side time value is smaller(occurrs
 earlier in the day) or equal(is the same time) than the one on the right-hand side*/
bool Time::operator<=(const Time& t) const
{
   Time tCopy(*this);

   if (tCopy<=t)
        return true;
   return false;
}

/* checks whether two time values are not equal*/
bool Time::operator!=(const Time& t) const
{
    Time tCopy(*this);
    if(tCopy==t)
        return false;
    return true;
}

/*checks whether left-hand side time value is bigger(occurrs
 later in the day) than the one on the right-hand side*/
bool operator>(const Time& t1, const Time& t2)
{
  int sum1 = t1.hour * 60 * 60 + t1.min * 60 + t1.sec;
  int sum2 = t2.hour * 60 * 60 + t2.min * 60 + t2.sec;

  if(sum1>sum2)
    return true;

  return false;
}

/*checks whether left-hand side time value is bigger(occurrs
 later in the day) or equal(is the same time) than the one on the right-hand side*/
bool operator>=(const Time& t1, const Time& t2)
{
  int sum1 = t1.hour * 60 * 60 + t1.min * 60 + t1.sec;
  int sum2 = t2.hour * 60 * 60 + t2.min * 60 + t2.sec;

  if(sum1>=sum2)
    return true;

  return false;
}

/*returns the elapsed time between its 2 arguments, in minutes. 
The first operand denotes the finish time and the second operand the start time*/
unsigned int operator-(const Time& t1, const Time& t2)
{
   int sum1 = t1.hour * 60 * 60 + t1.min * 60 + t1.sec;
   int sum2 = t2.hour * 60 * 60 + t2.min * 60 + t2.sec;
   int answ;

   if(t1>=t2)
   {   answ = sum1 - sum2;
		//does the rounding of minutes
       if(answ%60>=30)
        return answ/60 +1;
       else
        return answ/60;
   }

   else
   {   answ = (sum1 + 86400)- sum2;

       if(answ%60>=30)
        return answ/60 +1;
       else
        return answ/60;
   }
}

/*decrements time value by provided number of seconds*/
Time Time::operator-(unsigned int n) const 
{
  Time tCopy(*this);
  tCopy -= n;
  return tCopy;
}

/*decrements object's value by one and returns
 the new value*/
Time& operator--(Time& t) //prefix version
{
  t -= 1;
  return t;
}

/*decrements object's value by one and returns
 the old (non decremented) value*/
Time operator--(Time& t, int n) //postfix version
{
  Time tCopy = t;
  t -= 1;
  return tCopy;
}








