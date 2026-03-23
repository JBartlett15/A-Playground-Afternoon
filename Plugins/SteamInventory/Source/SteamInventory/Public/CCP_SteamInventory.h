// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "steam/steam_api.h"
#include "CCP_SteamInventory.generated.h"

USTRUCT(BlueprintType)
struct FSteamInventoryItem {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Steam")
	int32 itemDefinition = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Steam")
	int32 quantity = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Steam")
	int64 itemId = 0;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSteamInventoryReadySignature, bool, wasSuccessful, const TArray<FSteamInventoryItem>&, items);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAMINVENTORY_API UCCP_SteamInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCCP_SteamInventory();

	UPROPERTY(BlueprintAssignable, Category = "Steam")
	FOnSteamInventoryReadySignature onInventoryReady;

	UFUNCTION(BlueprintCallable, Category = "Steam")
	void RefreshInventory();

	UFUNCTION(BlueprintCallable, Category = "Steam")
	void DropItem(int32 ID);

	UFUNCTION(BlueprintCallable, Category = "Steam")
	void ManualGrantItem(int32 id, int32 amount);
private:
	void OnInventoryResult(SteamInventoryResultReady_t* callBack, bool IOFail);

	CCallResult<UCCP_SteamInventory, SteamInventoryResultReady_t> inventoryResultCallBack;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



		
};
