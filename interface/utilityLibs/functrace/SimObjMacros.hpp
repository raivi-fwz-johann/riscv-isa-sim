/**
 * @file SimObjMacros.hpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-01-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#define CURR_CID m_CId

#define GET_PROC (m_SimObj->m_SimWrapper.m_Simulator->get_core(CURR_CID))

#define GET_STATE (GET_PROC->get_state())
#define GET_STATE_MEMBER(member) (GET_STATE->member)

#define GET_CORE_INFO(member) (m_SimObj->m_CoreInfos[CURR_CID].member)

#define GET_MMU (GET_PROC->get_mmu())
#define GET_MMU_INFO_FUNC(func) (GET_MMU->func())