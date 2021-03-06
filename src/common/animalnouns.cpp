/*
    harvest-rogue is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    harvest-rogue is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with harvest-rogue.  If not, see <http://www.gnu.org/licenses/>.     */

#include "animalnouns.h"

std::string AnimalNouns[ANIMALNOUNS_MAX] = {"Aardvark",
                                            "Albatross",
                                            "Alligator",
                                            "Alpaca",
                                            "Ant",
                                            "Anteater",
                                            "Antelope",
                                            "Ape",
                                            "Armadillo",
                                            "Ass",
                                            "Donkey",
                                            "Baboon",
                                            "Badger",
                                            "Barracuda",
                                            "Bat",
                                            "Bear",
                                            "Beaver",
                                            "Bee",
                                            "Bison",
                                            "Boar",
                                            "Buffalo",
                                            "Galago",
                                            "Butterfly",
                                            "Camel",
                                            "Caribou",
                                            "Cat",
                                            "Caterpillar",
                                            "Cattle",
                                            "Chamois",
                                            "Cheetah",
                                            "Chicken",
                                            "Chimpanzee",
                                            "Chinchilla",
                                            "Chough",
                                            "Clam",
                                            "Cobra",
                                            "Cockroach",
                                            "Cod",
                                            "Cormorant",
                                            "Coyote",
                                            "Crab",
                                            "Crane",
                                            "Crocodile",
                                            "Crow",
                                            "Curlew",
                                            "Deer",
                                            "Dinosaur",
                                            "Dog",
                                            "Dogfish",
                                            "Dolphin",
                                            "Donkey",
                                            "Dotterel",
                                            "Dove",
                                            "Dragonfly",
                                            "Duck",
                                            "Dugong",
                                            "Dunlin",
                                            "Eagle",
                                            "Echidna",
                                            "Eel",
                                            "Eland",
                                            "Elephant",
                                            "Elephant seal",
                                            "Elk",
                                            "Emu",
                                            "Falcon",
                                            "Ferret",
                                            "Finch",
                                            "Fish",
                                            "Flamingo",
                                            "Fly",
                                            "Fox",
                                            "Frog",
                                            "Gaur",
                                            "Gazelle",
                                            "Gerbil",
                                            "Giant Panda",
                                            "Giraffe",
                                            "Gnat",
                                            "Gnu",
                                            "Goat",
                                            "Goose",
                                            "Goldfinch",
                                            "Goldfish",
                                            "Gorilla",
                                            "Goshawk",
                                            "Grasshopper",
                                            "Grouse",
                                            "Guanaco",
                                            "Guinea fowl",
                                            "Guinea pig",
                                            "Gull",
                                            "Hamster",
                                            "Hare",
                                            "Hawk",
                                            "Hedgehog",
                                            "Heron",
                                            "Herring",
                                            "Hippopotamus",
                                            "Hornet",
                                            "Horse",
                                            "Human",
                                            "Hummingbird",
                                            "Hyena",
                                            "Jackal",
                                            "Jaguar",
                                            "Jay",
                                            "Jay, Blue",
                                            "Jellyfish",
                                            "Kangaroo",
                                            "Koala",
                                            "Komodo dragon",
                                            "Kouprey",
                                            "Kudu",
                                            "Lapwing",
                                            "Lark",
                                            "Lemur",
                                            "Leopard",
                                            "Lion",
                                            "Llama",
                                            "Lobster",
                                            "Locust",
                                            "Loris",
                                            "Louse",
                                            "Lyrebird",
                                            "Magpie",
                                            "Mallard",
                                            "Manatee",
                                            "Marten",
                                            "Meerkat",
                                            "Mink",
                                            "Mole",
                                            "Monkey",
                                            "Moose",
                                            "Mouse",
                                            "Mosquito",
                                            "Mule",
                                            "Narwhal",
                                            "Newt",
                                            "Nightingale",
                                            "Octopus",
                                            "Okapi",
                                            "Opossum",
                                            "Oryx",
                                            "Ostrich",
                                            "Otter",
                                            "Owl",
                                            "Ox",
                                            "Oyster",
                                            "Panther",
                                            "Parrot",
                                            "Partridge",
                                            "Peafowl",
                                            "Pelican",
                                            "Penguin",
                                            "Pheasant",
                                            "Pig",
                                            "Pigeon",
                                            "Pony",
                                            "Porcupine",
                                            "Porpoise",
                                            "Prairie Dog",
                                            "Quail",
                                            "Quelea",
                                            "Rabbit",
                                            "Raccoon",
                                            "Rail",
                                            "Ram",
                                            "Rat",
                                            "Raven",
                                            "Red deer",
                                            "Red panda",
                                            "Reindeer",
                                            "Rhinoceros",
                                            "Rook",
                                            "Ruff",
                                            "Salamander",
                                            "Salmon",
                                            "Sand Dollar",
                                            "Sandpiper",
                                            "Sardine",
                                            "Scorpion",
                                            "Sea lion",
                                            "Sea Urchin",
                                            "Seahorse",
                                            "Seal",
                                            "Shark",
                                            "Sheep",
                                            "Shrew",
                                            "Shrimp",
                                            "Skunk",
                                            "Snail",
                                            "Snake",
                                            "Spider",
                                            "Squid",
                                            "Squirrel",
                                            "Starling",
                                            "Stingray",
                                            "Stinkbug",
                                            "Stork",
                                            "Swallow",
                                            "Swan",
                                            "Tapir",
                                            "Tarsier",
                                            "Termite",
                                            "Tiger",
                                            "Toad",
                                            "Trout",
                                            "Turkey",
                                            "Turtle",
                                            "Vicuña",
                                            "Viper",
                                            "Vulture",
                                            "Wallaby",
                                            "Walrus",
                                            "Wasp",
                                            "Water buffalo",
                                            "Weasel",
                                            "Whale",
                                            "Wolf",
                                            "Wolverine",
                                            "Wombat",
                                            "Woodcock",
                                            "Woodpecker",
                                            "Worm",
                                            "Wren",
                                            "Yak",
                                            "Zebra"};

