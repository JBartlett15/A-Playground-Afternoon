// Fill out your copyright notice in the Description page of Project Settings.


#include "CCP_SteamCloud.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"

// Sets default values for this component's properties
UCCP_SteamCloud::UCCP_SteamCloud()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UCCP_SteamCloud::SaveToSteam(FString slotName)
{
    if (!SteamRemoteStorage()) return false;

    FString relativePath = FString::Printf(TEXT("Saved/SaveGames/%s.sav"), *slotName);
    FString fullPath = FPaths::ProjectDir() + relativePath;

    TArray<uint8> saveData;
    if (!FFileHelper::LoadFileToArray(saveData, *fullPath))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load local .sav file: %s"), *fullPath);
        return false;
    }

    FString steamFileName = slotName + TEXT(".sav");
    bool success = SteamRemoteStorage()->FileWrite(TCHAR_TO_UTF8(*steamFileName), saveData.GetData(), saveData.Num());

    if (success)
    {
        UE_LOG(LogTemp, Log, TEXT("Successfully synced %s to Steam Cloud!"), *steamFileName);
    }

    return success;
}

bool UCCP_SteamCloud::LoadFromSteam(FString slotName)
{
    if (!SteamRemoteStorage()) return false;

    FString steamFileName = slotName + TEXT(".sav");

    if (SteamRemoteStorage()->FileExists(TCHAR_TO_UTF8(*steamFileName)))
    {
        int32 fileSize = SteamRemoteStorage()->GetFileSize(TCHAR_TO_UTF8(*steamFileName));
        TArray<uint8> fileData;
        fileData.AddUninitialized(fileSize);

        SteamRemoteStorage()->FileRead(TCHAR_TO_UTF8(*steamFileName), fileData.GetData(), fileSize);

        FString relativePath = FString::Printf(TEXT("Saved/SaveGames/%s.sav"), *slotName);
        FString fullPath = FPaths::ProjectDir() + relativePath;

        return FFileHelper::SaveArrayToFile(fileData, *fullPath);
    }
    return false;
}


// Called when the game starts
void UCCP_SteamCloud::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCCP_SteamCloud::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

