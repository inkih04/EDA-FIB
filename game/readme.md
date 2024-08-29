# Crematoria: A Game of Survival and Strategy

**Author:** Salvador Roura  
**Date:** November 24, 2023

## 1. Introduction

Crematoria is a planet in the Igneon System. Many years ago, its surface was uninhabitable due to extreme temperatures: incinerating in sunlight or freezing solid at night. A maximum-security prison was built underground, with limited surface access via elevators.

To increase security, genetically engineered hellhounds were released in the prison. These hybrids of dogs and reptiles would attack and devour any inmate in sight.

At least one Furyan, Riddick, was temporarily locked inside this prison. Furyans are human deviations with extraordinary physical abilities, making them fearsome warriors. Riddick escaped from Crematoria, but that’s another story...

> **Note:** This game is based on the film *The Chronicles of Riddick*. It’s not the best film ever made, but it’s wacky and weird, which are obviously good qualities.

---

## 2. Game Rules

This is a game for four players, identified by numbers from 0 to 3. Each player controls a group of Pioneers, aided by Furyans. The goals are to conquer as many cave cells and collect as many gems as possible.

- **Game Duration:** 120 rounds (numbered 0 to 119).
- **Units:**
  - **Pioneers:** Non-combatants who conquer cells and collect gems.
  - **Furyans:** Warriors who attack and protect Pioneers.
  - **Hellhounds:** Immortal creatures that devour everything in their path.
  - **Necromongers:** Combatants that attack Furyans and Pioneers.

### 2.1 Board Details

The board has two levels:
- **Underground (Level 0):** Contains cave and rock cells.
- **Outside (Level 1):** Divided into sunlit and night areas, with elevators connecting the two levels.

The map is circular horizontally, meaning the right of position `(i, 79, k)` connects to `(i, 0, k)`.

### 2.2 Movement and Combat

- Units can move horizontally, vertically, and diagonally.
- Pioneers and Furyans can use elevators to move between levels.
- The sun moves two columns to the right per round, killing all units in its path.

#### Combat Rules:
- **Pioneers:** Cannot attack.
- **Furyans:** Attack adjacent enemy units, dealing 25-50 damage.
- **Necromongers:** Attack adjacent Pioneers or Furyans, dealing 20-40 damage.
- **Hellhounds:** Devour all adjacent units at level 0.

#### Points System:
- 1 point per conquered cell.
- 30 points per gem collected.

The group with the most points at the end of 120 rounds wins.

---

## 3. Programming the Game

### 3.1 Running Your First Game

To run the game, follow these steps:

1. **Open a console** and navigate to the directory with the source code.
2. If using Linux, run:
   ```bash
   cp AIDummy.o.Linux AIDummy.o
   cp Board.o.Linux Board.o
