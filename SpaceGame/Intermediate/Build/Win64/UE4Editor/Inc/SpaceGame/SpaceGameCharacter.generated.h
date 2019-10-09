// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SPACEGAME_SpaceGameCharacter_generated_h
#error "SpaceGameCharacter.generated.h already included, missing '#pragma once' in SpaceGameCharacter.h"
#endif
#define SPACEGAME_SpaceGameCharacter_generated_h

#define SpaceGame_Source_SpaceGame_SpaceGameCharacter_h_12_RPC_WRAPPERS
#define SpaceGame_Source_SpaceGame_SpaceGameCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS
#define SpaceGame_Source_SpaceGame_SpaceGameCharacter_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASpaceGameCharacter(); \
	friend struct Z_Construct_UClass_ASpaceGameCharacter_Statics; \
public: \
	DECLARE_CLASS(ASpaceGameCharacter, ACharacter, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SpaceGame"), NO_API) \
	DECLARE_SERIALIZER(ASpaceGameCharacter)


#define SpaceGame_Source_SpaceGame_SpaceGameCharacter_h_12_INCLASS \
private: \
	static void StaticRegisterNativesASpaceGameCharacter(); \
	friend struct Z_Construct_UClass_ASpaceGameCharacter_Statics; \
public: \
	DECLARE_CLASS(ASpaceGameCharacter, ACharacter, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SpaceGame"), NO_API) \
	DECLARE_SERIALIZER(ASpaceGameCharacter)


#define SpaceGame_Source_SpaceGame_SpaceGameCharacter_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASpaceGameCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASpaceGameCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASpaceGameCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASpaceGameCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASpaceGameCharacter(ASpaceGameCharacter&&); \
	NO_API ASpaceGameCharacter(const ASpaceGameCharacter&); \
public:


#define SpaceGame_Source_SpaceGame_SpaceGameCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASpaceGameCharacter(ASpaceGameCharacter&&); \
	NO_API ASpaceGameCharacter(const ASpaceGameCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASpaceGameCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASpaceGameCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ASpaceGameCharacter)


#define SpaceGame_Source_SpaceGame_SpaceGameCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__CameraBoom() { return STRUCT_OFFSET(ASpaceGameCharacter, CameraBoom); } \
	FORCEINLINE static uint32 __PPO__FollowCamera() { return STRUCT_OFFSET(ASpaceGameCharacter, FollowCamera); }


#define SpaceGame_Source_SpaceGame_SpaceGameCharacter_h_9_PROLOG
#define SpaceGame_Source_SpaceGame_SpaceGameCharacter_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SpaceGame_Source_SpaceGame_SpaceGameCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	SpaceGame_Source_SpaceGame_SpaceGameCharacter_h_12_RPC_WRAPPERS \
	SpaceGame_Source_SpaceGame_SpaceGameCharacter_h_12_INCLASS \
	SpaceGame_Source_SpaceGame_SpaceGameCharacter_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SpaceGame_Source_SpaceGame_SpaceGameCharacter_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SpaceGame_Source_SpaceGame_SpaceGameCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	SpaceGame_Source_SpaceGame_SpaceGameCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	SpaceGame_Source_SpaceGame_SpaceGameCharacter_h_12_INCLASS_NO_PURE_DECLS \
	SpaceGame_Source_SpaceGame_SpaceGameCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SPACEGAME_API UClass* StaticClass<class ASpaceGameCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SpaceGame_Source_SpaceGame_SpaceGameCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
