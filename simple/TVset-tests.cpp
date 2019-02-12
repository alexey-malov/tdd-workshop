#include "pch.h"

using namespace std;

class TVSet
{
public:
	bool IsTurnedOn() const
	{
		return m_isOn;
	}
	void TurnOn()
	{
		m_isOn = true;
	}
	void TurnOff()
	{
		m_isOn = false;
	}

private:
	bool m_isOn = false;
};

SCENARIO("TVSet can be turned on and off", "[tv]")
{
	GIVEN("A turned off TV")
	{
		TVSet tv;

		WHEN("it is turned on")
		{
			INFO("The TV must be initially turned off");
			REQUIRE(!tv.IsTurnedOn());
			tv.TurnOn();
			THEN("it becomes turned on")
			{
				INFO("IsTurnedOn() returns true if TV is on");
				CHECK(tv.IsTurnedOn());
			}
		}

		AND_WHEN("it is turned off")
		{
			tv.TurnOff();
			THEN("it becomes turned off")
			{
				INFO("IsTurnedOn() msut return false if TV is off");
				CHECK(!tv.IsTurnedOn());
			}
		}
	}
}
