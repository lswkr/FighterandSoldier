// Fill out your copyright notice in the Description page of Project Settings.


#include "PracticeGameplayTags.h"

namespace PracticeGameplayTags
{
	/*Input Tags*/
	// DA_InputConfig의 inputtag배열에 meta = (TitleProperty = "InputTag")가 들어가 있어 InputTag는 따로 해줘야함, 즉, input용 태그랑 인풋액션용 태그랑 함께 추가해줘야함
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Melee,"InputTag.Attack.Melee");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Ranged, "InputTag.Attack.Ranged");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Ult, "InputTag.Attack.Ult");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld, "InputTag.MustBeHeld");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld_ExLazor, "InputTag.MustBeHeld.ExLazor");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_PickUp, "InputTag.PickUp");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Fire, "InputTag.Fire");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UltFire, "InputTag.UltFire");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UltCancel, "InputTag.UltCancel");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Roll, "InputTag.Roll");

	/*Fighter Tags*/
	UE_DEFINE_GAMEPLAY_TAG(Player_Fighter_Ability_Attack_Melee, "Player.Fighter.Ability.Attack.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Player_Fighter_Ability_Attack_Ranged, "Player.Fighter.Ability.Attack.Ranged");

	UE_DEFINE_GAMEPLAY_TAG(Player_Fighter_Event_Ult, "Player.Fighter.Event.Ult");

	/*Soldier Tags*/
	UE_DEFINE_GAMEPLAY_TAG(Player_Soldier_Weapon_Hitscan_DefaultGun, "Player.Soldier.Weapon.Hitscan.DefaultGun");
	UE_DEFINE_GAMEPLAY_TAG(Player_Soldier_Weapon_Hitscan_MK1, "Player.Soldier.Weapon.Hitscan.MK1");
	UE_DEFINE_GAMEPLAY_TAG(Player_Soldier_Weapon_Projectile_MK1, "Player.Soldier.Weapon.Projectile.MK1");
	UE_DEFINE_GAMEPLAY_TAG(Player_Soldier_Weapon_Projectile_MK2, "Player.Soldier.Weapon.Projectile.MK2");


	UE_DEFINE_GAMEPLAY_TAG(Player_Soldier_Ability_Attack_Melee, "Player.Soldier.Ability.Attack.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Player_Soldier_Ability_Attack_Fire, "Player.Soldier.Ability.Attack.Fire");
	UE_DEFINE_GAMEPLAY_TAG(Player_Soldier_Ability_PickUp_Gun, "Player.Soldier.Ability.PickUp.Gun");
	UE_DEFINE_GAMEPLAY_TAG(Player_Soldier_Ability_PickUp_Bullet, "Player.Soldier.Ability.PickUp.Bullet");
	UE_DEFINE_GAMEPLAY_TAG(Player_Soldier_Ability_UltFire, "Player.Soldier.Ability.UltFire");
	UE_DEFINE_GAMEPLAY_TAG(Player_Soldier_Ability_UltCancel, "Player.Soldier.Ability.UltCancel");


	UE_DEFINE_GAMEPLAY_TAG(Player_Soldier_SetByCaller_AttackType_LineTrace, "Player.Soldier.SetByCaller.AttackType.LineTrace");
	UE_DEFINE_GAMEPLAY_TAG(Player_Soldier_SetByCaller_AttackType_Projectile, "Player.Soldier.SetByCaller.AttackType.Projectile");

	UE_DEFINE_GAMEPLAY_TAG(Player_Soldier_Event_UltFire, "Player.Soldier.Event.UltFire");
	UE_DEFINE_GAMEPLAY_TAG(Player_Soldier_Event_UltCancel, "Player.Soldier.Event.UltCancel");
	UE_DEFINE_GAMEPLAY_TAG(Player_Soldier_Event_UnintentionalCancel, "Player.Soldier.Event.UnIntentionalCancel");

	UE_DEFINE_GAMEPLAY_TAG(Player_Soldier_Status_BulletsFull, "Player.Soldier.Status.BulletsFull");
	UE_DEFINE_GAMEPLAY_TAG(Player_Soldier_Status_BulletsEmpty, "Player.Soldier.Status.BulletsEmpty");
	UE_DEFINE_GAMEPLAY_TAG(Player_Soldier_Status_Targetting, "Player.Soldier.Status.Targetting");

	/*Player Tags*/
	UE_DEFINE_GAMEPLAY_TAG(Player_Shared_Ability_Ult, "Player.Shared.Ability.Ult");
	UE_DEFINE_GAMEPLAY_TAG(Player_Shared_Ability_HitPause, "Player.Shared.Ability.HitPause");
	UE_DEFINE_GAMEPLAY_TAG(Player_Shared_Ability_ExLazor, "Player.Shared.Ability.ExLazor");
	UE_DEFINE_GAMEPLAY_TAG(Player_Shared_Ability_Roll, "Player.Shared.Ability.Roll");
	UE_DEFINE_GAMEPLAY_TAG(Player_Shared_Ability_PickUp, "Player.Shared.Ability.PickUp");

	UE_DEFINE_GAMEPLAY_TAG(Player_Shared_Event_HitPause, "Player.Shared.Event.HitPause");
	UE_DEFINE_GAMEPLAY_TAG(Player_Shared_Event_Consume, "Player.Shared.Event.Consume");

	UE_DEFINE_GAMEPLAY_TAG(Player_Shared_Status_UltFull, "Player.Shared.Status.UltFull");
	UE_DEFINE_GAMEPLAY_TAG(Player_Shared_Status_UltNone, "Player.Shared.Status.UltNone");
	UE_DEFINE_GAMEPLAY_TAG(Player_Shared_Status_UltCharging, "Player.Shared.Status.UltCharging");
	UE_DEFINE_GAMEPLAY_TAG(Player_Shared_Status_ExLazoring, "Player.Shared.Status.ExLazoring");
	UE_DEFINE_GAMEPLAY_TAG(Player_Shared_Status_Rolling, "Player.Shared.Status.Rolling");
	UE_DEFINE_GAMEPLAY_TAG(Player_Shared_Status_LevelUp, "Player.Shared.Status.LevelUp");

	UE_DEFINE_GAMEPLAY_TAG(Player_Shared_SetByCaller_UltGain, "Player.Shared.SetByCaller.UltGain");
	/*Enemy Tags*/
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_SpawningItem, "Enemy.Ability.SpawningItem");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Robot_Ability_Launch, "Enemy.Robot.Ability.Launch");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Strafing, "Enemy.Status.Strafing");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_UnderAttack, "Enemy.Status.UnderAttack");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_SpawningItem, "Enemy.Status.SpawningItem");

	/*Shared Tags*/
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit, "Shared.Event.MeleeHit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Attack_Ranged, "Shared.Event.Attack.Ranged");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Dead, "Shared.Status.Dead");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Invincible, "Shared.Status.Invincible");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Left, "Shared.Status.HitReact.Left");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Right, "Shared.Status.HitReact.Right");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Front, "Shared.Status.HitReact.Front");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Back, "Shared.Status.HitReact.Back");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_DontTouchUlt, "Shared.Status.DontTouchUlt");


	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_AttackType_ComboAttack, "Shared.SetByCaller.AttackType.ComboAttack");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseExp, "Shared.SetByCaller.BaseExp");


	UE_DEFINE_GAMEPLAY_TAG(Type_Fighter, "Type.Fighter");
	UE_DEFINE_GAMEPLAY_TAG(Type_Soldier, "Type.Soldier");
	UE_DEFINE_GAMEPLAY_TAG(Type_Enemy, "Type.Enemy");

	/*Item Tags*/
	UE_DEFINE_GAMEPLAY_TAG(Item_Gun, "Item.Gun");
	UE_DEFINE_GAMEPLAY_TAG(Item_Kit, "Item.Kit");
	UE_DEFINE_GAMEPLAY_TAG(Item_Bullet, "Item.Bullet");


	/*Game Data Tags*/
	UE_DEFINE_GAMEPLAY_TAG(GameData_Level_PayloadGameModeMap_Soldier, "GameData.Level.PayloadGameModeMap");
	UE_DEFINE_GAMEPLAY_TAG(GameData_Level_MainMenuMap, "GameData.Level.MainMenuMap");
	UE_DEFINE_GAMEPLAY_TAG(GameData_PlayerPawn_Fighter, "GameData.PlayerPawn.Fighter");
	UE_DEFINE_GAMEPLAY_TAG(GameData_PlayerPawn_Soldier, "GameData.PlayerPawn.Soldier");


}