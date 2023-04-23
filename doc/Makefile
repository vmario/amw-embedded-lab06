.PHONY: all clean

TARGET = manual.pdf
SOURCE = manual.md rotary-encoder-internal-structure.png encoder-timing.svg

all: $(TARGET)

$(TARGET): $(SOURCE)
	pandoc $< -o $@ --template eisvogel --listings --metadata date="`date +%F`"

clean:
	rm -f $(TARGET)
