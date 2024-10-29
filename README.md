# Monte-Carlo Algorithm Project

[![ENJMIN](https://img.shields.io/badge/%20ENJMIN-c1002a?style=for-the-badge)](https://enjmin.cnam.fr/)
![Cplusplus](https://img.shields.io/badge/made%20in%20c%2B%2B-ffffff?style=for-the-badge&color=white)

## Presentation

This is a school project. The objectives were plural :

- Discover and use the Monte-Carlo Algorithm in the field of games
video games
- Develop this algorithm with the aim of optimising a deck of cards for
a collectible card game (CCG) such as Magic the Gatering or
Hearthstone
- Produce data to analyse the results obtained

This was done in several stages. Foremost, we had to develop the card game and its rules and enable two computer bots to play a game. Then we had to enable the bots to play a large number of games by allowing them to modify their deck between each series of games in order to improve and optimize their deck. And finally, we had to extend the rules of the game to make it more complex.

## Personal addition

In order to produce results quickly, the code has been developed with speed
optimum speed in mind. So, where possible, we reduce the number of loops and
the number of loops and checks. We have also added multithreading
to increase speed. For example, in the latest version of the project for
2 million games played, it takes between 6 and 8s.

## Results

The project meets the initial objectives we set ourselves. We are able to produce several decks and optimize each one. Or analyze whether certain cards are too recurrent or not recurrent enough.
On the other hand, there are several possible areas for improvement:
- Optimize the Set list itself by counting when cards leave or join the deck in order to
join the deck to identify the best and worst cards.
- Optimize the deck against several different decks, themselves optimized. This could be done using multithreading, for example.
Unfortunately, these improvements could not be implemented due to a lack of time.

---

The [project report](/Data/Rapport%20du%20TP%20Optimisation.pdf) (french only) can be consulted in this repository.