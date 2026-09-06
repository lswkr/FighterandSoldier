// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UI/PawnUIComponent.h"
#include "Widgets/PracticeWidgetBase.h"

void UPawnUIComponent::RegisterDrawnWidget(UPracticeWidgetBase* InWidgetToRegister)
{
	DrawnWidgets.Add(InWidgetToRegister);
}

void UPawnUIComponent::RemoveDrawnWidgetsIfAny()
{
	if (DrawnWidgets.IsEmpty())
	{
		return;
	}

	for (UPracticeWidgetBase* DrawnWidget : DrawnWidgets)
	{
		if (DrawnWidget)
		{
			DrawnWidget->RemoveFromParent();
		}
	}
	DrawnWidgets.Empty();
}
