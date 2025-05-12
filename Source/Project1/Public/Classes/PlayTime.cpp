// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayTime.h"

PlayTime::PlayTime()
	: Hours(0),
	Minutes(0),
	Seconds(0)
{
}

PlayTime::~PlayTime()
{
}

void PlayTime::AddSecond()
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

FString PlayTime::ToString() const
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
