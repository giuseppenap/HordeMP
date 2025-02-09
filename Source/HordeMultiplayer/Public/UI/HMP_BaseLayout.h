// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "HMP_WidgetLayerManager.h"
#include "Blueprint/UserWidget.h"
#include "HMP_BaseLayout.generated.h"

/**
 * 
 */
UCLASS()
class HORDEMULTIPLAYER_API UHMP_BaseLayout : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	TMap<FGameplayTag, UHMP_WidgetLayerManager*> Layers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	TMap<FGameplayTag, TSoftClassPtr<UUserWidget>> InitialScreens;

	UPROPERTY(BlueprintReadOnly, Category = "Config")
	TSubclassOf<UHMP_WidgetLayerManager> LayerBP;

public:

	UFUNCTION(BlueprintCallable, Category = Widget)
	bool RegisterLayer(FGameplayTag LayerName, UHMP_WidgetLayerManager* LayerWidget);

	UFUNCTION(BlueprintCallable, Category = Widget)
	bool UnregisterLayer(FGameplayTag LayerName);

	UFUNCTION(BlueprintCallable, Category = Widget)
	UUserWidget* PushContentToLayer(FGameplayTag LayerName, TSoftClassPtr<UUserWidget> WidgetClass);

	UFUNCTION(BlueprintCallable, Category = Widget)
	void PopContentFromLayer(FGameplayTag LayerName);

	UFUNCTION(BlueprintCallable, Category = Widget)
	void ClearAllLayers();

	UFUNCTION(BlueprintCallable, Category = Widget)
	void ClearAllLayersExcept(FGameplayTag ExceptionLayerName);

	UFUNCTION(BlueprintCallable, Category = Widget)
	void ClearLayer(FGameplayTag LayerName);

	UFUNCTION(BlueprintCallable, Category = Widget)
	void PushInitialScreens();

	UFUNCTION(BlueprintCallable, Category = Widget)
	virtual void NativeConstruct() override;

	
	
	
};
