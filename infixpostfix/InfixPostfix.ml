include List;;
include Stack;; 
include Char;; 

let pow base exponent =
  if exponent < 0 then invalid_arg "exponent négatif" else
    let rec aux accumulator base = function
      | 0 -> accumulator
      | 1 -> base * accumulator
      | e when (e mod 2 = 0) -> aux accumulator (base * base) (e / 2)
      | e -> aux (base * accumulator) (base * base) ((e - 1) / 2) in
    aux 1 base exponent;; 

let rec factorielle n =
  if n = 0 then 1 else  n * factorielle (n-1);;

let numcheck c =
  if c = '+' || c = '*' || c = '/' || c='^' || c= '!' || c= '-' then false else true ;;

let evaluator s =
  let rec aux p l r= match l with
    | [] -> if is_empty p = false then aux (p) (l) (r^((pop(p)))) else r
    | t::q when t = "!" -> push ((string_of_int(factorielle(int_of_string(pop(p)))))) (p); aux p q r
    | t::q when t = "+" -> push ( (string_of_int(int_of_string(pop(p)) + int_of_string(pop(p))))) (p); aux p q r
    | t::q when t = "-" -> push ( (string_of_int(int_of_string(pop(p)) - int_of_string(pop(p))))) (p); aux p q r
    | t::q when t = "*" -> push ( (string_of_int(int_of_string(pop(p)) * int_of_string(pop(p))))) (p); aux p q r
    | t::q when t = "/" -> push ( (string_of_int(int_of_string(pop(p)) / int_of_string(pop(p))))) (p); aux p q r
    | t::q when t = "^" -> push ( (string_of_int(pow (int_of_string(pop(p))) (int_of_string(pop(p)))))) (p); aux p q r 
    | t::q -> push t p; aux p q r 
  in aux (Stack.create()) (String.split_on_char ',' s) ("");;

print_endline (evaluator(read_line()));;
  
  