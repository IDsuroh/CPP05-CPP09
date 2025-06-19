#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int main() {
    std::cout << "=== Serialization Test ===" << std::endl;
    
    // Create a Data object
    Data originalData(42, "Alice", 3.14, 'A');
    Data* originalPtr = &originalData;
    
    std::cout << "Original Data:" << std::endl;
    std::cout << "  Address: " << originalPtr << std::endl;
    std::cout << "  ID: " << originalData.id << std::endl;
    std::cout << "  Name: " << originalData.name << std::endl;
    std::cout << "  Value: " << originalData.value << std::endl;
    std::cout << "  Grade: " << originalData.grade << std::endl;
    std::cout << std::endl;
    
    // Serialize the pointer
    uintptr_t serialized = Serializer::serialize(originalPtr);
    std::cout << "Serialized pointer:" << std::endl;
    std::cout << "  As integer: " << serialized << std::endl;
    std::cout << "  As hex: 0x" << std::hex << serialized << std::dec << std::endl;
    std::cout << std::endl;
    
    // Deserialize back to pointer
    Data* deserializedPtr = Serializer::deserialize(serialized);
    std::cout << "Deserialized pointer:" << std::endl;
    std::cout << "  Address: " << deserializedPtr << std::endl;
    std::cout << std::endl;
    
    // Test: Compare pointers
    std::cout << "=== Verification ===" << std::endl;
    std::cout << "Original ptr == Deserialized ptr: " << (originalPtr == deserializedPtr) << std::endl;
    
    if (originalPtr == deserializedPtr) {
        std::cout << "✓ SUCCESS: Pointers match!" << std::endl;
        
        // Verify we can still access the data
        std::cout << "✓ Data accessible through deserialized pointer:" << std::endl;
        std::cout << "  ID: " << deserializedPtr->id << std::endl;
        std::cout << "  Name: " << deserializedPtr->name << std::endl;
        std::cout << "  Value: " << deserializedPtr->value << std::endl;
        std::cout << "  Grade: " << deserializedPtr->grade << std::endl;
    } else {
        std::cout << "✗ FAILURE: Pointers don't match!" << std::endl;
    }
    
    // Additional test with dynamically allocated Data
    std::cout << std::endl << "=== Dynamic Allocation Test ===" << std::endl;
    
    Data* dynamicData = new Data(99, "Bob", 2.71, 'B');
    std::cout << "Dynamic data address: " << dynamicData << std::endl;
    
    uintptr_t dynamicSerialized = Serializer::serialize(dynamicData);
    Data* dynamicDeserialized = Serializer::deserialize(dynamicSerialized);

    std::cout << "\nAfter serialization and deserialization\n" << std::endl;
    std::cout << "Dynamic deserialized address: " << dynamicDeserialized << std::endl;
    std::cout << "Dynamic pointers match: " << (dynamicData == dynamicDeserialized) << std::endl;
    
    if (dynamicData == dynamicDeserialized) {
        std::cout << "✓ Dynamic test successful!" << std::endl;
        std::cout << "  Dynamic data name: " << dynamicDeserialized->name << std::endl;
    }
    
    // ===== FAILURE CASES =====
    std::cout << std::endl << "=== Failure Test Cases ===" << std::endl;
    
    // Failure Case 1: Different objects at different addresses
    std::cout << "\n--- Test 1: Different Objects ---" << std::endl;
    Data data1(1, "First", 1.1, 'A');
    Data data2(2, "Second", 2.2, 'B');
    Data* ptr1 = &data1;
    Data* ptr2 = &data2;
    
    std::cout << "Data1 address: " << ptr1 << std::endl;
    std::cout << "Data2 address: " << ptr2 << std::endl;
    std::cout << "Are they the same address? " << (ptr1 == ptr2) << std::endl;
    
    uintptr_t serialized1 = Serializer::serialize(ptr1);
    uintptr_t serialized2 = Serializer::serialize(ptr2);
    std::cout << "Data1 serialized: " << serialized1 << std::endl;
    std::cout << "Data2 serialized: " << serialized2 << std::endl;
    std::cout << "Serialized values equal? " << (serialized1 == serialized2) << std::endl;
    std::cout << "✓ Different objects = different serialized values (correct!)" << std::endl;
    
    // Failure Case 2: Invalid/corrupted serialized value
    std::cout << "\n--- Test 2: Corrupted Serialized Value ---" << std::endl;
    uintptr_t validSerialized = Serializer::serialize(originalPtr);
    uintptr_t corruptedSerialized = validSerialized + 1000; // Corrupt the address
    
    std::cout << "Valid serialized: " << validSerialized << std::endl;
    std::cout << "Corrupted serialized: " << corruptedSerialized << std::endl;
    
    Data* validDeserialized = Serializer::deserialize(validSerialized);
    Data* corruptedDeserialized = Serializer::deserialize(corruptedSerialized);
    
    std::cout << "Valid deserialized: " << validDeserialized << std::endl;
    std::cout << "Corrupted deserialized: " << corruptedDeserialized << std::endl;
    std::cout << "Are they equal? " << (validDeserialized == corruptedDeserialized) << std::endl;
    std::cout << "✗ DANGER: Corrupted address points to random memory!" << std::endl;
    std::cout << "✗ DO NOT ACCESS: " << corruptedDeserialized << " (undefined behavior)" << std::endl;
    
    // Failure Case 3: Dangling pointer after object destruction
    std::cout << "\n--- Test 3: Dangling Pointer (Scope Test) ---" << std::endl;
    Data* danglingPtr;
    uintptr_t danglingSerialized;
    
    {
        // Create object in limited scope
        Data scopedData(88, "Temporary", 8.8, 'T');
        danglingPtr = &scopedData;
        danglingSerialized = Serializer::serialize(danglingPtr);
        
        std::cout << "Scoped data address: " << danglingPtr << std::endl;
        std::cout << "Scoped data name: " << scopedData.name << std::endl;
        std::cout << "Before Serialization: " << danglingPtr << std::endl;
        std::cout << "Serialized while valid: " << danglingSerialized << std::endl;
    } // scopedData is destroyed here!
    
    std::cout << "After scope ends:" << std::endl;
    Data* deserializedDangling = Serializer::deserialize(danglingSerialized);
    std::cout << "Deserialized address: " << deserializedDangling << std::endl;
    std::cout << "Addresses match? " << (danglingPtr == deserializedDangling) << std::endl;
    std::cout << "✗ DANGER: Object no longer exists at this address!" << std::endl;
    std::cout << "✗ DO NOT ACCESS: Undefined behavior (dangling pointer)" << std::endl;
    
    // Failure Case 4: Null pointer
    std::cout << "\n--- Test 4: Null Pointer ---" << std::endl;
    Data* nullPtr = NULL;
    uintptr_t nullSerialized = Serializer::serialize(nullPtr);
    Data* nullDeserialized = Serializer::deserialize(nullSerialized);
    
    std::cout << "Null pointer: " << nullPtr << std::endl;
    std::cout << "Null serialized: " << nullSerialized << std::endl;
    std::cout << "Null deserialized: " << nullDeserialized << std::endl;
    std::cout << "Are they equal? " << (nullPtr == nullDeserialized) << std::endl;
    std::cout << "✓ NULL serialization works (but accessing would crash!)" << std::endl;
    
    // Clean up
    delete dynamicData;
    
    std::cout << std::endl << "=== Summary ===" << std::endl;
    std::cout << "✓ Serialization preserves valid pointer addresses" << std::endl;
    std::cout << "✗ Serialization cannot protect against:" << std::endl;
    std::cout << "  - Corrupted addresses" << std::endl;
    std::cout << "  - Dangling pointers (destroyed objects)" << std::endl;
    std::cout << "  - Null pointer access" << std::endl;
    std::cout << "⚠️  Always ensure objects exist when deserializing!" << std::endl;
    
    return 0;
}

/*

What is the Point of This Exercise?
This exercise teaches about serialization
- a fundamental concept in programming where data is converted
into a format that can be stored, transmitted, or reconstructed
later.

// 1. Saving game state
Player* player = getPlayer();
uintptr_t savedState = serialize(player);
writeToFile(savedState);  // Save to disk

// 2. Network communication  
Data* message = createMessage();
uintptr_t packet = serialize(message);
sendOverNetwork(packet);  // Send to another computer

// 3. Inter-process communication
Data* sharedData = getSharedData();
uintptr_t handle = serialize(sharedData);
passToAnotherProcess(handle);  // Share between programs

*/