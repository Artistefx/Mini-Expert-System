# Expert System for Programming Language Recommendation

A simple console-based expert system that recommends a programming language based on user responses to a set of questions.

## Introduction

This project implements a basic expert system in C for recommending a programming language to a user based on their responses to a series of questions. The expert system follows a rule-based approach and uses a predefined set of questions, answers, and rules to make a recommendation.

## How It Works

1. The program presents a series of questions to the user.
2. The user selects answers to these questions.
3. Based on the user's answers, the expert system evaluates the rules and suggests a suitable programming language.

## Code Structure

The code is organized into several data structures and functions:

- `Question` Structure: Represents a question and points to the possible answers.
- `Reponse` Structure: Represents a user's response and points to the next question.
- `Regle` Structure: Represents a rule containing a sequence of responses.
- `Base_Regle` Structure: Forms a chain of rules and attaches a conclusion.
- `User_Answer` Structure: Represents the user's answers in a linked list.

The main functions are responsible for creating questions, answers, rules, and recommendations. The `Interface` function interacts with the user to gather responses, while the `Moteur_Inference` function matches user responses with rules to provide a recommendation.

## Getting Started

1. Clone or download this repository.
2. Compile the code using a C compiler.
3. Run the compiled executable to start the expert system.

## Usage

1. Run the compiled executable.
2. Answer the questions presented to you.
3. The expert system will suggest a suitable programming language based on your answers.

## Contributors

- [Hamza KERBOUB](#) - GitHub Profile: [Artistefx](#)

## License

This project is licensed under the [MIT License](LICENSE).
