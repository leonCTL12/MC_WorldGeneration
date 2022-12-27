// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockBase.h"
#include "GrassBlock.h"
#include "SoilBlock.h"
#include "BlockPool.h"

BlockPool::BlockPool(TSubclassOf<AGrassBlock> grass, TSubclassOf<ASoilBlock> soil) : grassBlockClass(grass), soilBlockClass(soil) {}

BlockPool::~BlockPool()
{
}

ABlockBase* BlockPool::CreateBlock(UWorld* world, BlockType blockType)
{
	TSubclassOf<ABlockBase> blockClass = LocateBlockClass(blockType);

	std::stack<ABlockBase*>* pool = LocatePool(blockType);

	if (pool->empty()) {
		return world->SpawnActor<ABlockBase>(blockClass, FVector(0), FRotator(0));
	}
	else {
		ABlockBase* block = pool->top();
		block->SetActive(true);
		pool->pop();
		return block;
	}
}

void BlockPool::DestroyBlock(ABlockBase* block, BlockType blockType)
{
	block->SetActive(false);
	std::stack<ABlockBase*>* pool = LocatePool(blockType);
	pool->push(block);
}

std::stack<ABlockBase*>* BlockPool::LocatePool(BlockType blockType)
{
	switch (blockType)
	{
	case grass:
		return &grassBlockPool;
	case soil:
		return &soilBlockPool;
	default:
		return nullptr;
	}
}

TSubclassOf<ABlockBase> BlockPool::LocateBlockClass(BlockType blockType)
{
	switch (blockType)
	{
	case grass:
		return grassBlockClass;
	case soil:
		return soilBlockClass;
	default:
		return nullptr;
	}
}

