/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* ScriptData
SDName: Boss_Baroness_Anastari
SD%Complete: 90
SDComment: MC disabled
SDCategory: Stratholme
EndScriptData */


#include "def_stratholme.h"

#define SPELL_BANSHEEWAIL   16565
#define SPELL_BANSHEECURSE    16867
#define SPELL_SILENCE    18327
//#define SPELL_POSSESS   17244

struct boss_baroness_anastariAI : public ScriptedAI
{
    boss_baroness_anastariAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = (InstanceScript*)me->GetInstanceScript();
    }

    InstanceScript* pInstance;

    uint32 BansheeWail_Timer;
    uint32 BansheeCurse_Timer;
    uint32 Silence_Timer;
    //uint32 Possess_Timer;

    void Reset() override
    {
        BansheeWail_Timer = 1000;
        BansheeCurse_Timer = 11000;
        Silence_Timer = 13000;
        //Possess_Timer = 35000;
    }

     void JustDied(Unit* Killer) override
     {
         if (pInstance)
             pInstance->SetData(TYPE_BARONESS,IN_PROGRESS);
     }

    void UpdateAI(const uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        //BansheeWail
        if (BansheeWail_Timer < diff)
        {
            if (rand()%100 < 95)
                DoCast(me->GetVictim(),SPELL_BANSHEEWAIL);
            //4 seconds until we should cast this again
            BansheeWail_Timer = 4000;
        }else BansheeWail_Timer -= diff;

        //BansheeCurse
        if (BansheeCurse_Timer < diff)
        {
            if (rand()%100 < 75)
                DoCast(me->GetVictim(),SPELL_BANSHEECURSE);
            //18 seconds until we should cast this again
            BansheeCurse_Timer = 18000;
        }else BansheeCurse_Timer -= diff;

        //Silence
        if (Silence_Timer < diff)
        {
            if (rand()%100 < 80)
                DoCast(me->GetVictim(),SPELL_SILENCE);
            //13 seconds until we should cast this again
            Silence_Timer = 13000;
        }else Silence_Timer -= diff;

        //Possess
        /*            if (Possess_Timer < diff)
        {
        //Cast
          if (rand()%100 < 65)
        {
        Unit* target = NULL;
        target = SelectTarget(SELECT_TARGET_RANDOM,0);
        if (target)DoCast(target,SPELL_POSSESS);
        }
        //50 seconds until we should cast this again
        Possess_Timer = 50000;
        }else Possess_Timer -= diff;
        */

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_boss_baroness_anastari(Creature *_Creature)
{
    return new boss_baroness_anastariAI (_Creature);
}

void AddSC_boss_baroness_anastari()
{
    OLDScript *newscript;
    newscript = new OLDScript;
    newscript->Name="boss_baroness_anastari";
    newscript->GetAI = &GetAI_boss_baroness_anastari;
    sScriptMgr->RegisterOLDScript(newscript);
}

