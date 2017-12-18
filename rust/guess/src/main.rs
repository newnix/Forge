//
// practice program from the rust handbook v2
//
extern crate rand;

use std::io;
use std::cmp::Ordering;
use rand::Rng;

fn main() {
    let secret = rand::thread_rng().gen_range(0,101); // Inclusive lower bound, exclusive upper
    println!("Guess the number!");
        loop { // Guess there's no loop types in Rust
        println!("Please input your guess.");
        let mut guess = String::new(); // How to create a new string buffer that can hold volitile data
        // Rust still supports passing variables as a reference to a location in memory, like C, which
        // is nice to have.
        io::stdin().read_line(&mut guess) // Rust has OOP principals like function.method/class.method
            .expect("Failed to read line"); // Basically the equivalent of if (ret == NULL)
        // Now we need to convert the guessed string to an integer of some sort
        let guess: u32 = match guess.trim().parse() { // basic error handling 
            Ok(guess) => guess,
            Err(_) => continue,
        };

        println!("You guessed: {}", guess);

        match guess.cmp(&secret) {
            Ordering::Less => println!("Too Low!"),
            Ordering::Greater => println!("Too High!"),
            Ordering::Equal => {
                println!("Winner!");
                break; // Exit, we're done here.
            }
        }
    }
}
