#include "pch.h"

using namespace std;

class InvalidOperation
	: public runtime_error
{
public:
	InvalidOperation(const string& msg)
		: runtime_error(msg)
	{
	}
};

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
	int GetCurrentChannel() const
	{
		return m_isOn ? m_channel : 0;
	}
	void SelectChannel(int channel)
	{
		if (!m_isOn)
		{
			throw InvalidOperation("TV is turned off");
		}
		if (channel < MIN_CHANNEL || channel > MAX_CHANNEL)
		{
			throw out_of_range("Channel is out of range");
		}
		m_channel = channel;
	}

private:
	static constexpr int MIN_CHANNEL = 1;
	static constexpr int MAX_CHANNEL = 999;
	bool m_isOn = false;
	int m_channel = 1;
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

SCENARIO("A TV after first turn-on is at channel 1")
{
	TVSet tv;
	tv.TurnOn();
	CHECK(tv.GetCurrentChannel() == 1);
}

SCENARIO("A turned on TV can select channel from 1 to 999")
{
	GIVEN("A tv")
	{
		TVSet tv;
		WHEN("tv is turned on")
		{
			tv.TurnOn();
			THEN("It can select channels from 1 to 999")
			{
				tv.SelectChannel(999);
				CHECK(tv.GetCurrentChannel() == 999);
				tv.SelectChannel(1);
				CHECK(tv.GetCurrentChannel() == 1);
				tv.SelectChannel(150);
				CHECK(tv.GetCurrentChannel() == 150);
			}
		}
	}
}

SCENARIO("A turned off TV can't select channels")
{
	GIVEN("A TV")
	{
		TVSet tv;
		WHEN("TV is turned off")
		{
			THEN("It is at channel 0")
			{
				CHECK(tv.GetCurrentChannel() == 0);
			}

			THEN("It can't select channels")
			{
				CHECK_THROWS_AS(tv.SelectChannel(1), InvalidOperation);
				CHECK_THROWS_WITH(tv.SelectChannel(1), "TV is turned off");
				CHECK(tv.GetCurrentChannel() == 0);
			}
		}
	}
}

SCENARIO("TV can't select a channel beyond the 1..999 range")
{
	SECTION("A turned on TV")
	{
		TVSet tv;
		tv.TurnOn();
		SECTION("  can't select channel less than 1")
		{
			CHECK_THROWS_AS(tv.SelectChannel(0), out_of_range);
			CHECK(tv.GetCurrentChannel() == 1);
		}

		SECTION("  can't select channel greater than 999")
		{
			CHECK_THROWS_AS(tv.SelectChannel(1000), out_of_range);
			CHECK(tv.GetCurrentChannel() == 1);
		}
	}
}

SCENARIO("A TV must restore the previously selected channel")
{
	GIVEN("A TV with selected channel")
	{
		TVSet tv;
		tv.TurnOn();
		tv.SelectChannel(42);
		WHEN("TV is turned off and on")
		{
			tv.TurnOff();
			tv.TurnOn();
			THEN("it restores previously selected channel")
			{
				CHECK(tv.GetCurrentChannel() == 42);
			}
		}
	}
}