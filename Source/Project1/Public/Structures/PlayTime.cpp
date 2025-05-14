// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayTime.h"

FPlayTime::FPlayTime()
	: Hours(0),
	Minutes(0),
	Seconds(0)
{
}

FPlayTime::FPlayTime(const uint64 InHours, const uint8 InMinutes, const uint8 InSeconds)
{
	SetTime(InHours, InMinutes, InSeconds);
}

void FPlayTime::IncrementSecond()
{
	++Seconds;

	if (Seconds == 60)
	{
		++Minutes;
		Seconds = 0;

		if (Minutes == 60)
		{
			++Hours;
			Minutes = 0;
		}
	}
}

void FPlayTime::SetTime(const uint64 NewHours, const uint8 NewMinutes, const uint8 NewSeconds)
{
	// Don't allow the play time minutes or seconds to be set to 60 or higher
	static constexpr uint8 MaxMinutes{ 60 };
	static constexpr uint8 MaxSeconds{ 60 };

	check(NewMinutes < MaxMinutes);
	check(NewSeconds < MaxSeconds);

	Hours = NewHours;
	Minutes = NewMinutes;
	Seconds = NewSeconds;
}

FString FPlayTime::ToString() const
{
	// Build display string
	FString DisplayString(TEXT(""));
	DisplayString.Reserve(9); // Reserve enough characters for format: HHH:MM:SS

	DisplayString.Append((Hours < 10) ?
		FString::Printf(TEXT("0%d"), Hours) :
		FString::Printf(TEXT("%d"), Hours)
	);

	DisplayString.AppendChar(':');

	DisplayString.Append((Minutes < 10) ?
		FString::Printf(TEXT("0%d"), Minutes) :
		FString::Printf(TEXT("%d"), Minutes)
	);

	DisplayString.AppendChar(':');

	DisplayString.Append((Seconds < 10) ?
		FString::Printf(TEXT("0%d"), Seconds) :
		FString::Printf(TEXT("%d"), Seconds)
	);

	return DisplayString;
}
