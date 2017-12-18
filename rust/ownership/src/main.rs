fn main() { // s is not valid here, duh, not declared yet
    // here we can play with s
    let mut s = String::from("hello");
    s.push_str(", world!"); // push_str() appends a string literal to a string variable
    println!("{}",s); // should print 'hello, world!'
    move_pointer();
    clone_pointer();
    move_primitives();
    takes_ownership(give()); // value of s enters the function and is no longer valid here
    // println!("{}",s); is invalid here
    let x = 10;
    makes_copy(x);
    let s1 = flip(give());
    println!("after flip(): {}", s1);
    let (s2, z) = touple(s1);
    println!("the length of '{}' is {}", s2, z);
    let x = length(&s2);
    println!("length of s2: {}",x);
    let mut s3 = String::from("I'm string s3!");
    append(&mut s3);
    println!("{}",s3);
} // at this point, s is destroyed/invalid, no longer in scope

fn move_pointer() {
    // simple display of a "move" operation in rust
    let s1 = String::from("s1 data");
    println!("s1: {}",s1);
    let s2 = s1; // this migrates the pointer from s1 to s2
    println!("s2: {}",s2);
    // this call is invalid now
    // println!("{}",s1);
}

fn clone_pointer() {
    // this function actually copies the data represented by the pointer 
    let s1 = String::from("s1 data");
    println!("s1: {}",s1);
    let mut s2 = s1.clone(); // s2 now represents a separate string
    s2.push_str(", modified in a cloned string"); // changes not represented in s1
    println!("s2: {}",s2);
    println!("s1: {}",s1);
}

fn move_primitives() {
    let x = 5; // obvious
    let y = x; // again, obvious, assign y to the value of x
    // according to move_pointer(), this should make x invalid
    // however, due to ints having a fixed size, this acts like a call to .clone()
    println!("x: {}\ny: {}", x, y);
}

fn takes_ownership(s: String) { // s comes into scope here
    println!("{}", s);
} // s is dropped

fn makes_copy(int: i32) { // int comes into scope
    println!("{}", int);
} // int leaves scope, nothing special happens

fn give() -> String {
    // give() will move it's return value to the function calling it
    let s = String::from("take this string");
    s
}

fn flip(given: String) -> String {
    // flip() returs the string it was given
    given
}

fn touple(s: String) -> (String, usize) { // simple function returning a touple
    let len = s.len(); // returns the length of the given string
    (s, len)
}

// using refrences, we avoid ownership issues when passing values to a function
fn length(s: &String) -> usize {
    s.len()
}

// change a string passed to this function
fn append(s: &mut String) {
    s.push_str("\nI've seen the light of append()!")
}
