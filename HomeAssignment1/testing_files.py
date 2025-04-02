import base64
import os

def generateData(size):
    return os.urandom(size)

def encodeData(data):
    return base64.a85encode(data)
    
def decodeData(data):
    return base64.a85decode(data)

def saveToFile(data, fileName):
    with open(fileName, "wb") as file:
        file.write(data)

if __name__ == "__main__":
    dataSize = 100
    data = generateData(dataSize)
    encodedData = encodeData(data)
    saveToFile(encodedData, "encoded.txt")
    decodedData = decodeData(encodedData)
    saveToFile(decodedData, "decoded.txt")
    
     



