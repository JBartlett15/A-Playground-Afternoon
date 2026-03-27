// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "steam/steam_api.h"
#include "CPP_SteamAchievement.generated.h"

USTRUCT(BlueprintType, Category = "Steam")
struct FAchievementData {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Steam")
	FString ID;

	UPROPERTY(BlueprintReadOnly, Category = "Steam")
	FString name;

	UPROPERTY(BlueprintReadOnly, Category = "Steam")
	bool isUnlocked;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAMINVENTORY_API UCPP_SteamAchievement : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPP_SteamAchievement();

	UFUNCTION(BlueprintCallable, Category = "Steam")
	bool UnlockSteamAchievement(FString achievementID);

	UFUNCTION(BlueprintCallable, Category = "Steam")
	void UpdateStat(FString stat, int32 amount);

	UFUNCTION(BlueprintCallable, Category = "Steam")
	int32 GetStatAmount(FString stat);

	UFUNCTION(BlueprintCallable, Category = "Steam")
	TArray<FAchievementData> GetAllAchievements();

	UFUNCTION(BlueprintCallable, Category = "Steam")
	bool HasGotAchievement(FString achievementID);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
