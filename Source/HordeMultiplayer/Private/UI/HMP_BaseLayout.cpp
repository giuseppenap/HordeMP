// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HMP_BaseLayout.h"

void UHMP_BaseLayout::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UHMP_BaseLayout::RegisterLayer(FGameplayTag LayerName, UHMP_WidgetLayerManager* LayerWidget)
{
	if (LayerWidget && !Layers.Contains(LayerName))
	{
		Layers.Add(LayerName, LayerWidget);
		return true;
	}
	return false;
}

bool UHMP_BaseLayout::UnregisterLayer(FGameplayTag LayerName)
{
	if (UHMP_WidgetLayerManager** FoundLayer = Layers.Find(LayerName))
	{
		if (*FoundLayer)
		{
			(*FoundLayer)->RemoveFromParent();
		}
		return (Layers.Remove(LayerName) > 0);
	}
	return false;
}

UUserWidget* UHMP_BaseLayout::PushContentToLayer(FGameplayTag LayerName, TSoftClassPtr<UUserWidget> WidgetClass)
{
	if (UHMP_WidgetLayerManager** FoundLayer = Layers.Find(LayerName))
	{
		if (*FoundLayer)
		{
			return (*FoundLayer)->PushContent(WidgetClass);
		}
	}
	return nullptr;
}

void UHMP_BaseLayout::PopContentFromLayer(FGameplayTag LayerName)
{
	if (UHMP_WidgetLayerManager** FoundLayer = Layers.Find(LayerName))
	{
		if (*FoundLayer)
		{
			(*FoundLayer)->PopContent();
		}
	}
}

void UHMP_BaseLayout::ClearAllLayers()
{
	TArray<UHMP_WidgetLayerManager*> Widgets;
	Layers.GenerateValueArray(Widgets);

	for (UHMP_WidgetLayerManager* Layer : Widgets)
	{
		if (Layer)
		{
			Layer->ClearStack();
		}
	}
}

void UHMP_BaseLayout::ClearAllLayersExcept(FGameplayTag ExceptionLayerName)
{
	for (const auto& Elem : Layers)
	{
		if (Elem.Key != ExceptionLayerName && Elem.Value)
		{
			Elem.Value->ClearStack();
		}
	}
}

void UHMP_BaseLayout::ClearLayer(FGameplayTag LayerName)
{
	if (UHMP_WidgetLayerManager** FoundLayer = Layers.Find(LayerName))
	{
		if (*FoundLayer)
		{
			(*FoundLayer)->ClearStack();
		}
	}
}

void UHMP_BaseLayout::PushInitialScreens()
{
	for (const auto& Elem : InitialScreens)
	{
		TSoftClassPtr<UUserWidget>* MatchingLayer = InitialScreens.Find(Elem.Key);
		PushContentToLayer(Elem.Key, *MatchingLayer);
		UE_LOG(LogTemp, Warning, TEXT("PushedTheScreen"));
	}
}


