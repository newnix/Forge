fn main() {
    let number = 3;
    // basic logic statement
    if number < 5 {
        println!("{} is less than 5",number);
    } else {
        println!("{} is not less than 5",number);
    }
    // using a logical statement to assign values
    let condition = true;
    let number = if condition {
        10
    } else {
        11
    };
    println!("The value of number is: {}",number);
    liftoff();
    array_loop();
    loop_foreach();
    range_loop();
}

// simple while loop 
fn liftoff() {
    let mut number = 10;

    while number != 0 {
        println!("{}!", number);
        number = number - 1;
    }
    println!("LIFTOFF!");
}

// loop over an array index
fn array_loop() {
    let a = [10, 20, 30, 40, 50];
    let mut index = 0; 

    while index < 5 {
        println!("while loop");
        println!("a[{}]: {}",index, a[index]);
        index = index + 1;
    }
}

// foreach style loop
fn loop_foreach() {
    let a = [10, 20, 30, 40, 50];

    // eerily similar to bash
    for element in a.iter() {
        println!("foreach loop");
        println!("{}",element);
    }
}

// for loop with range
fn range_loop() {
    for number in (0..10).rev() {
        println!("{}!",number);
    }
    println!("LIFTOFF 2: Electric Bugaloo");
}
