from random import randint
from os import system

def compile_cpp(file_name):
    """Compile specified C++ file and create executable"""
    cpp_file = f"{file_name}.cpp"
    output_file = file_name
    system(f"echo Compiling {cpp_file}")
    system(f"g++ {cpp_file} -o {output_file}")
    return output_file

def generate_input():
    """Create input for a single test case."""
    with open("in", "w") as input_file:
        input_file.write(str(randint(1, 10)))

def generate_output(executable):
    """Generate output using the specified executable."""
    system(f"./{executable} < in > {executable}.out")
    with open(f"{executable}.out", "r") as output_file:
        return output_file.read().strip()

def clear(files_to_clear):
    """Removed specified files in the current folder."""
    files_to_clear_str = " ".join(files_to_clear)
    system(f"rm {files_to_clear_str}")

def are_equal(output_list):
    """Check if all elements in the list are equal."""
    return len(set(output_list)) == 1

def main():
    # GIVEN the number of test cases and the file names
    n_test_cases = 100
    file_names = ["wa", "ac"]
    executables = [compile_cpp(file_name) for file_name in file_names]
    # WHEN the outputs generated by both
    # executables on each test case are compared
    for test_case in range(1, n_test_cases + 1):
        print(f'Test Case {test_case}: ', end="")
        generate_input()
        outputs = [generate_output(executable) for executable in executables]
        if not are_equal(outputs):
            print("WRONG ANSWER")
            clear(executables)
            exit(0)
        print("OK")
    # THEN they should coincide and the final verdict must be Accepted
    print("ACCEPTED")
    outputs = [f"{executable}.out" for executable in executables]
    clear([*file_names, *outputs, "in"])

if __name__ == "__main__":
    main()