// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "HMP_WidgetLayerManager.generated.h"


class UBorder;
class UUserWidget;


/**
 * 
 */
UCLASS()
class HORDEMULTIPLAYER_API UHMP_WidgetLayerManager : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	TArray<UUserWidget*> Stack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Objects")
	UUserWidget* PushedWidget;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UBorder> LayoutBorder;

public:


	
	UFUNCTION(BlueprintImplementableEvent, Category = "UI Layer")
	UUserWidget* PushContent(const TSoftClassPtr<UUserWidget>& WidgetClass);

	UFUNCTION(BlueprintImplementableEvent, Category = "UI Layer")
	void PopContent();

	UFUNCTION(BlueprintCallable, Category = "UI Layer")
	void ClearStack();

	UFUNCTION(BlueprintCallable, Category = "UI Layer")
	UUserWidget* Peek();

	UFUNCTION(BlueprintCallable, Category = "UI Layer")
	void CollapseTop();

	UFUNCTION(BlueprintCallable, Category = "UI Layer")
	void ShowTop();

	UFUNCTION(BlueprintCallable, Category = "UI Layer")
	FText GetStackListNames() const;

	UFUNCTION(BlueprintCallable, Category = "UI Layer")
	bool IsEmpty();

	/*UFUNCTION()
	virtual void NativeConstruct() override;*/
	
};