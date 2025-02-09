// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HMP_WidgetLayerManager.h"


void UHMP_WidgetLayerManager::ClearStack()
{
    for (UUserWidget* Widget : Stack)
    {
        if (Widget)
        {
            Widget->RemoveFromParent();
        }
    }
    Stack.Empty();
    LayoutBorder->ClearChildren();
}

UUserWidget* UHMP_WidgetLayerManager::Peek()
{
    if (IsEmpty())
    {
        return nullptr;
    }

    return Stack.Num() > 0 ? Stack.Last() : nullptr;
}

void UHMP_WidgetLayerManager::CollapseTop()
{
    if (UUserWidget* LastWidget = Peek())
    {
        LastWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UHMP_WidgetLayerManager::ShowTop()
{
    if (UUserWidget* TopWidget = Peek())
    {
        TopWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
    }
}

FText UHMP_WidgetLayerManager::GetStackListNames() const
{
    TArray<FString> StackNames;
    for (UUserWidget* Widget : Stack)
    {
        if (Widget)
        {
            StackNames.Add(Widget->GetName());
        }
    }
    FString JoinedStackNames = FString::Join(StackNames, TEXT("\r\n"));
    return FText::FromString(JoinedStackNames);
}

bool UHMP_WidgetLayerManager::IsEmpty()
{
    return Stack.IsEmpty();
}





/*void UHMP_WidgetLayerManager::NativeConstruct()
{
    Super::NativeConstruct();

    if (LayoutBorder)
    {
        UE_LOG(LogTemp, Warning, TEXT("LayoutBorder initialized: %s"), *LayoutBorder->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("LayoutBorder is null in NativeConstruct"));
    }

    LayoutBorder = Cast<UBorder>(GetWidgetFromName(TEXT("LayoutBorder")));

    if (LayoutBorder)
    {
        UE_LOG(LogTemp, Warning, TEXT("LayoutBorder found: %s"), *LayoutBorder->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("LayoutBorder is null"));
    }

    if (!LayoutBorder)
    {
        // Create a new Border widget
        LayoutBorder = NewObject<UBorder>(this, UBorder::StaticClass());
        UE_LOG(LogTemp, Warning, TEXT("LayoutBorder created"));
        LayoutBorder->SetVerticalAlignment(VAlign_Fill);
        LayoutBorder->SetHorizontalAlignment(HAlign_Fill);
        
    }
    
}*/

/*
UUserWidget* UHMP_WidgetLayerManager::PushContent(TSoftClassPtr<UUserWidget> WidgetUserClass)
{

    
    if (!WidgetUserClass.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("Widget class must be valid"));
        return nullptr;
    }

    UClass* LoadedWidgetClass = WidgetUserClass.LoadSynchronous();
    if (!LoadedWidgetClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Widget Class"));
        return nullptr;
    }

    APlayerController* OwningPlayer = GetOwningPlayer();
    if (!OwningPlayer)
    {
        UE_LOG(LogTemp, Warning, TEXT("No Owning Player"));
        return nullptr;
    }

    PushedWidget = CreateWidget<UUserWidget>(OwningPlayer, LoadedWidgetClass);
    if (!PushedWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to create Widget"));
        return nullptr;
    }

    CollapseTop();
    
    
    if (LayoutBorder)
    {
        LayoutBorder->ClearChildren();
        Stack.Add(PushedWidget);
        LayoutBorder->AddChild(PushedWidget);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("LayoutBorder not found"));
    }
    ShowTop();
    return PushedWidget;
}

void UHMP_WidgetLayerManager::PopContent()
{
    if (!IsEmpty())
    {
        UUserWidget* TopWidget = Peek();
        if (TopWidget)
        {
            TopWidget->RemoveFromParent();
            Stack.Remove(Stack.Last());
            LayoutBorder->ClearChildren();
            TopWidget = Peek();
            if (TopWidget)
            {
                TopWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
                LayoutBorder->AddChild(TopWidget);
            }
        }
    }
}
*/
