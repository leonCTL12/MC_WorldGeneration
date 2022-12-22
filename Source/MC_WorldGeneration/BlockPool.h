// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BlockBase.h"
#include "BlockType.h"
#include "CoreMinimal.h"
#include <stack>

/**
 * 
 */
class MC_WORLDGENERATION_API BlockPool
{
public:
	BlockPool(TSubclassOf<AGrassBlock> grass);
	~BlockPool();

private:
	
private:
	std::stack<ABlockBase*> grassBlockPool;
	TSubclassOf<AGrassBlock> grassBlockClass;

public:
	ABlockBase* CreateBlock(UWorld* world, BlockType blockType);
	void DestroyBlock(ABlockBase* block, BlockType blockType);
private:
	std::stack<ABlockBase*>* LocatePool(BlockType blockType);
	TSubclassOf<ABlockBase> LocateBlockClass(BlockType blockType);
};

