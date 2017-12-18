fn new_func() { // one nice thing about rust, is that functions can be declared anywhere
    println!("Hello from new_func()");
}

fn main() {
    println!("Hello, world!");
    let x: i32 = {
        let y = 4; 
        y * y
    };
    prnt_num(plus_one(x));
    new_func();
    yanf(five(),3);
}

fn prnt_num(x: i32) {
    println!("The value of x is: {}",x);
}

fn yanf(x: i32, y:i32) {
    println!("x: {}",x);
    println!("y: {}",y);
}

// unfortunately, there's no way to chain variable assignments like in C:
// let x = (let y = 6); is invalid

// Declare a function with a return value
fn five() -> i32 {
    5 // this feels wrong
}

// add +1 
fn plus_one(x: i32) -> i32 {
    x + 1
}
