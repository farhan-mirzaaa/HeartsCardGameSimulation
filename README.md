# Hearts Card Game Simulation

This is a console-based application written in C++ as part of a technical assessment for the interview process at LMKR. It simulates a 4-player trick-taking card game where all players are implemented as computer players.

## Dependencies

### C++ Standard Library (C++11 or later)
- The project utilizes standard C++ features such as:
  - `std::vector`
  - `std::string`
  - `std::shared_ptr`
  - `std::algorithm`
  - `std::chrono`
- No external header-only libraries (e.g., from [https://github.com/p-ranav/awesome-hpp](https://github.com/p-ranav/awesome-hpp)) are used, adhering to assignment constraints.

### Visual Studio
- **Version**: Visual Studio 2022

### Microsoft Unit Testing Framework for C++
- The test project (`HeartsCardGameSimulationTestProject`) leverages this framework to showcase unit and integration testing skills.

## Projects

### Main Project: HeartsCardGameSimulation
- A complete implementation featuring 4 computer players.

### Test Project: HeartsCardGameSimulationTestProject
- Focuses on demonstrating unit testing and integration testing capabilities.

## Architecture

The architecture is centered around a `CGame` class, supported by manager classes for players and cards. This design ensures a clean simulation loop while maintaining component decoupling for future enhancements.

### Architecture Overview

The system is divided into core components:

- **Cards Management**:
  - Classes such as `CCard`, `CCardSuit`, `CCardRank`, and `CCardPointsAllocator` encapsulate card properties (suit, rank, points).
  - Cards are comparable via overloaded operators, enabling sorting and trick resolution.
  - `CCardsFactory` implements the Factory pattern to centralize card instantiation and ensure consistency.

- **Player Management**:
  - `CPlayer` serves as the base class, with derived classes `CComputerPlayer` and `CHumanPlayer`, promoting polymorphism for card selection and passing.
  - `CPlayerManager` handles player creation via `CPlayerFactory`, tracks the player lead, and updates scores.
  - Computer players feature rule-based AI logic for passing and playing, while human player logic remains unimplemented.

- **Game and Round Logic**:
  - `CGame` initializes players and cards, runs the main loop until a player reaches 100 points, and manages round creation and execution.
  - `CRound` oversees the round lifecycle, including trick execution.

- **Utility Components**:
  - `CConsoleLogger` (Singleton) manages console output.
  - `CScoreCalculator` computes scores based on taken cards.

## Design Decisions and Trade-offs

This implementation adheres to SOLID and DRY principles. Examples include:

- **Single Responsibility Principle (SRP)**:
  - `CCardsManager` is dedicated to operations like creation, shuffling, and distribution.
  - `CRound` focuses solely on the round lifecycle.

- **Open-Closed Principle (OCP)**:
  - New player behaviors can be introduced by creating subclasses of `CPlayer`.

- **Liskov Substitution Principle (LSP)**:
  - Derived classes (`CComputerPlayer`, `CHumanPlayer`) can seamlessly replace `CPlayer` in collections like `m_vecPlayers`, as they implement pure virtual methods such as `GetPassCards` and `ChooseCard`.

- **Interface Segregation Principle (ISP)**:
  - (Not explicitly detailed; ensure interfaces are minimal and specific if applicable.)

- **Dependency Inversion Principle (DIP)**:
  - `CGame` depends on abstractions (e.g., `CPlayer` pointers) rather than concrete player classes.

### Modular Structure for Future Growth
- **Adding Human Input**: The `CHumanPlayer` class can be extended to handle human input.
- **Rule Variations**: New penalties can be added to `CScoreCalculator` without refactoring.
- **Scalability**: Vectors for cards and players support easy expansion to more players or custom decks.
- **Error Handling and Logging**: Centralized logging via `CConsoleLogger` can be utilized for exception logging.