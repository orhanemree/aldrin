import sys
import os

has_pillow = True
try:
    from PIL import Image
except Exception:
    has_pillow = False
    
EXAMPLES_PATH = "../examples"
EXAMPLE_OUTPUT_PATH = "../examples/output"
EXPECTED_OUTPUT_PATH = "./expected"


def run_example(test_name: str):
    """
    Run example. Generate it's output. Convert .ppm to .png (to make it human-visible) Delete executable. Return output .ppm as text.
    """
    
    os.chdir(EXAMPLES_PATH)
    os.system(f"gcc {test_name}.c -o {test_name} -lm")
    os.system(f"./{test_name}")
    os.system(f"rm {test_name}")

    if has_pillow:
        image = Image.open(f"output/{test_name}.ppm")
        image.save(f"output/{test_name}.png")
    
    with open(f"output/{test_name}.ppm") as f:
        output = f.read()
        
    os.chdir("../test")
    
    return output
    

def run_test(test_name: str) -> bool:
    """
    Run test. Compare output with expected. Return is same.
    """
    
    try:
        output = run_example(test_name)
        
        with open(f"{os.path.join(EXPECTED_OUTPUT_PATH, test_name)}.ppm") as f:
            return f.read() == output
        
    except Exception:
        return False


def record_test(test_name: str) -> bool:
    """
    Copy output of example to expected folder. Return is succeed.
    """
    
    try:
        output = run_example(test_name)
        
        with open(f"{os.path.join(EXPECTED_OUTPUT_PATH, test_name)}.ppm", "w") as f:
            f.write(output)
        
        return True
            
    except Exception:
        return False
    

def display_help():
    print("USAGE:\n")
    print("Run all test:        main.py\n")
    print("Run single test:     main.py <TEST_NAME>")
    print("  Example: main.py lines\n")
    print("Record all tests:    main.py record\n")
    print("Record single test:  main.py record <TEST_NAME>")
    print("  Example: main.py record triangles\n")
    print("Print this message:  main.py help")
    

def main():
    if len(sys.argv) == 1:
        # run all tests
        tests = [f for f in os.listdir(EXAMPLES_PATH) if ".c" in f]
        
        for test in tests:
            test_name = test.split(".")[0]
            
            success = run_test(test_name)
            if success: print(f"🟢 Test `{test_name}` passed.")
            else: print(f"🔴 Test `{test_name}` failed.")
                
    elif sys.argv[1] == "record":
        
        if len(sys.argv) > 2:
            # record single test
            test_name = sys.argv[2]
            
            if test_name+".c" in os.listdir(EXAMPLES_PATH):
                success = record_test(test_name)
                if success: print(f"🟢 Test `{test_name}` recorded.")
                else: print(f"🔴 Test `{test_name}` could not be recorded.")
            else:
                print(f"🟠 Test `{test_name}` is not exist.")
            
        else:
            # record all tests
            tests = [f for f in os.listdir(EXAMPLES_PATH) if ".c" in f]
            
            for test in tests:
                test_name = test.split(".")[0]
                
                success = record_test(test_name)
                if success: print(f"🟢 Test `{test_name}` recorded.")
                else: print(f"🔴 Test `{test_name}` could not be recorded.")
                
    elif sys.argv[1] == "help":
        display_help()
        
    else:
        # run sinlge test
        test_name = sys.argv[1]
        
        if test_name+".c" in os.listdir(EXAMPLES_PATH):
            success = run_test(test_name)
            if success: print(f"🟢 Test `{test_name}` passed.")
            else: print(f"🔴 Test `{test_name}` failed.")
        else:
            print(f"🟠 Test `{test_name}` is not exist.")


if __name__ == "__main__":
    main()
