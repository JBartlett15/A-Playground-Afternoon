// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_SteamAchievement.h"

// Sets default values for this component's properties
UCPP_SteamAchievement::UCPP_SteamAchievement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UCPP_SteamAchievement::UnlockSteamAchievement(FString achievementID)
{
	if (!SteamUserStats()) {
		UE_LOG(LogTemp, Log, TEXT("No Steam User"));
		return false;
	}

	bool successful = SteamUserStats()->SetAchievement(TCHAR_TO_UTF8(*achievementID));

	if (successful) {
		SteamUserStats()->StoreStats();

		UE_LOG(LogTemp, Log, TEXT("Steam Achievement Unlocked"));
	}

	return successful;
}

void UCPP_SteamAchievement::UpdateStat(FString stat, int32 amount)
{
	if (SteamUserStats()) {
		SteamUserStats()->SetStat(TCHAR_TO_ANSI(*stat), amount);
		SteamUserStats()->StoreStats();
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("No steam user"));
	}

}

int32 UCPP_SteamAchievement::GetStatAmount(FString stat)
{
	if (!SteamUserStats()) {
		return -1;
	}
	int32 statGot;

	SteamUserStats()->GetStat(TCHAR_TO_ANSI(*stat), &statGot);

	return statGot;
}

TArray<FAchievementData> UCPP_SteamAchievement::GetAllAchievements()
{
	TArray<FAchievementData> allUnlocked;

	if (!SteamUserStats()) {
		return allUnlocked;
	}

	uint32 numberOfAchievements = SteamUserStats()->GetNumAchievements();

	for (uint32 i = 0; i < numberOfAchievements; i++) {
		const char* name = SteamUserStats()->GetAchievementName(i);
		bool unlocked = false;
		SteamUserStats()->GetAchievement(name, &unlocked);

		FAchievementData data;
		data.ID = UTF8_TO_TCHAR(name);
		data.isUnlocked = unlocked;

		data.name = UTF8_TO_TCHAR(SteamUserStats()->GetAchievementDisplayAttribute(name, "Name"));

		allUnlocked.Add(data);

	}

	return allUnlocked;
}

bool UCPP_SteamAchievement::HasGotAchievement(FString achievementID)
{
	if (!SteamUserStats()) {
		return false;
	}

	bool isUnlocked = false;

	if (SteamUserStats()->GetAchievement(TCHAR_TO_UTF8(*achievementID), &isUnlocked)) {
		return isUnlocked;
	}

	return false;
}


// Called when the game starts
void UCPP_SteamAchievement::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCPP_SteamAchievement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

