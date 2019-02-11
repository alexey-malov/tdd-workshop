#include "pch.h"

using namespace std;

class Button
{
public:
	void DoOnClick(function<void()> onClick)
	{
		m_onClick = onClick;
	}

private:
	function<void()> m_onClick;
};

class ICalculatorController
{
public:
	virtual void OnCalculateClicked() = 0;

	virtual ~ICalculatorController() = default;
};

class ICalculatorView
{
public:
	virtual int GetFirstSummand() const = 0;
	virtual int GetSecondSummand() const = 0;
	virtual void SetSum(int sum) = 0;

	virtual ~ICalculatorView() = default;
};

class CalculationService
{
public:
	int CalculateSum(int a, int b)
	{
		return a + b;
	}
};

class CalculatorController : public ICalculatorController
{
public:
	CalculatorController(CalculationService& calculator, ICalculatorView& view)
		: m_calculator(calculator)
		, m_view(view)
	{
	}

	void OnCalculateClicked() override
	{
		m_view.SetSum(m_calculator.CalculateSum(m_view.GetFirstSummand(), m_view.GetSecondSummand()));
	}

private:
	CalculationService& m_calculator;
	ICalculatorView& m_view;
};

class CalculatorWindow : public ICalculatorView
{
public:
	CalculatorWindow(CalculationService& service)
		: m_controller(service, *this)
	{
		m_calculate.DoOnClick([this] { m_controller.OnCalculateClicked(); });
	}
	Button m_calculate;
	CalculatorController m_controller;
};

struct MockView : ICalculatorView
{
	int firstSummand = 0;
	int secondSummand = 0;
	int sum = 0;

	int GetFirstSummand() const override
	{
		return firstSummand;
	}

	int GetSecondSummand() const override
	{
		return secondSummand;
	}

	void SetSum(int s) override
	{
		sum = s;
	}
};

SCENARIO("A sum of two summands is displayed on Calculate button click")
{
	GIVEN("A controller with view and calculator")
	{
		MockView view;
		view.firstSummand = 10;
		view.secondSummand = 30;

		CalculationService calculator;
		CalculatorController controller(calculator, view);

		WHEN("Calculate button is clicked")
		{
			controller.OnCalculateClicked();

			THEN("view displays the sum of two summands returned by calculator")
			{
				CHECK(view.sum == view.firstSummand + view.secondSummand);
			}
		}
	}
}
