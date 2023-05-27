// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/QuestItems/BaseQuestItem.h"
#include "Characters/GDTV_PlayerCharacter.h"

void ABaseQuestItem::OnItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AGDTV_PlayerCharacter* Player = Cast<AGDTV_PlayerCharacter>(OtherActor))
	{
		Destroy();
	}
}
