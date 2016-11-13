/*
 * Copyright (C) 2005-2008 MaNGOS <http://www.mangosproject.org/>
 *
 * Copyright (C) 2008 Trinity <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef TRINITYCORE_TEMPSUMMON_H
#define TRINITYCORE_TEMPSUMMON_H

#include "Creature.h"
#include "ObjectAccessor.h"

class TC_GAME_API TemporarySummon : public Creature
{
    public:
        explicit TemporarySummon(uint64 summoner = 0);
        ~TemporarySummon() override{};
        void Update(uint32 time) override;
        void Summon(TempSummonType type, uint32 lifetime);
        void UnSummon();
        void SaveToDB(uint32 mapid, uint8 spawnMask) override { }
        TempSummonType GetSummonType() { return m_type; }
        Unit* GetSummoner() const override { return m_summoner ? ObjectAccessor::GetUnit(*this, m_summoner) : nullptr; }
        bool DespawnOnDeath();
    private:
        TempSummonType m_type;
        uint32 m_timer;
        uint32 m_lifetime;
        uint64 m_summoner;
};
#endif

