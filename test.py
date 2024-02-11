import hnswlib

# Example Python code
import ctypes

def interpret_capsule_as_bytes(capsule):
    # Check if the capsule is valid
    if ctypes.pythonapi.PyCapsule_IsValid(capsule, b"byte_capsule"):
        # Get the pointer from the capsule
        ptr = ctypes.pythonapi.PyCapsule_GetPointer(capsule, b"byte_capsule")
        if ptr:
            # Get the size of the data (assuming it's null-terminated or has a known size)
            size = 0
            while ctypes.cast(ptr + size, ctypes.c_char).value != 0:
                size += 1

            # Create a bytes object from the data
            data_bytes = ctypes.string_at(ptr, size)
            return data_bytes

    raise TypeError("Invalid byte_capsule")



def dist(a, b, c):
    print("In dist")
    print(a, b, c)
    print(interpret_capsule_as_bytes(a))
    return 1.0


dim = 1
num_elements = 1000
p = hnswlib.Index(dist_func=dist, dim=1)
p.init_index(max_elements=num_elements, ef_construction=20, M=10)
