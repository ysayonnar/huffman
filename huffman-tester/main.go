package main

import (
	"bytes"
	"flag"
	"fmt"
	"math/rand"
	"os"
)

func main() {
	if len(os.Args) < 2 || (os.Args[1] != "generate" && os.Args[1] != "check") {
		fmt.Println("commands: `generate -s <size> -n <filename>` `check -n <filename>`")
		return
	}

	command := os.Args[1]
	os.Args = os.Args[1:]

	var fileSize int
	var fileName string

	flag.IntVar(&fileSize, "s", 1024, "amount of bytes for file")
	flag.StringVar(&fileName, "n", "data", "name of file")

	flag.Parse()

	switch command {
	case "generate":
		err := GenerateFile(fileSize, fileName)
		if err != nil {
			panic(err)
		}
	case "check":
		err := CheckFile(fileName)
		if err != nil {
			panic(err)
		}
	default:
		fmt.Println("invalid command!")
	}
}

func GenerateFile(fileSize int, fileName string) error {
	if fileSize < 1 {
		return fmt.Errorf("filesize is to small: %d bytes", fileSize)
	}
	if fileName == "" {
		return fmt.Errorf("invalid filename")
	}

	file, err := os.Create(fmt.Sprintf("%s.txt", fileName))
	if err != nil {
		return fmt.Errorf("error while creating file: %w", err)
	}
	defer file.Close()

	var buf bytes.Buffer
	for range fileSize {
		symbol := byte(rand.Intn(256))
		_, err = buf.Write([]byte{symbol})
		if err != nil {
			return fmt.Errorf("error while writing to file: %w", err)
		}
	}

	_, err = file.Write(buf.Bytes())
	if err != nil {
		return fmt.Errorf("error while writing to file: %w", err)
	}

	return nil
}

func CheckFile(fileName string) error {
	return nil
}
