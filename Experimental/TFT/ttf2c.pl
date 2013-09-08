#!/usr/bin/perl

use strict;
use GD;
use Data::Dumper;

my $file = shift;
my $points = shift;

if(!$points) 
{
    $points = 8;
}

if(!-f $file)
{
	die("Unable to open $file");
}

my $out = $file . ".cpp";
my $name = $file;

$name =~ s/\-//g;
if($file =~ /^(.*)\.ttf/i)
{
	$out = $1 . ".cpp";
	$name = $1;
}

if($name =~ /([^\/]+)$/)
{
    $out = $1 . ".cpp";
    $name = $1;
}

my $chardata;   # Array to store character data

my $char = 0;  # Start with the space character

my $size = findFontSize($file,$points);

print "Font size:\n";
print "Top: " . $size->{top} . "\n";
print "Bottom: " . $size->{bottom} . "\n";
print "Left: " . $size->{left} . "\n";
print "Right: " . $size->{right} . "\n";

print "Width: " . $size->{width} . "\n";
print "Height: " . $size->{height} . "\n";
print "Origin: " . $size->{origin}->{x} . "," . $size->{origin}->{y} . "\n";

$size->{bpl} = int($size->{width} / 8) + 1;

print "Bytes per line: " . $size->{bpl} . "\n";

if ($size->{bpl} > 4) {
    print "ERROR: Font is too wide!\n";
    exit(10);
}

my $img = GD::Image->new($size->{width},$size->{height});
my $bg = $img->colorAllocate(0,0,0);
my $fg = $img->colorAllocate(255,255,255);

my $fontdata;
my $offset = 0;

open(OUT,">$out");
print OUT "#include <TFT.h>\n\n";
print OUT "const uint8_t Fonts::" . $name . "[] = {\n";

printf(OUT "    %d, %d, 0x%02X, 0x%02X,\n",
    $size->{height}, $size->{bpl}, 0, 255);

while($char < 256)
{
    $img->filledRectangle(0,0,$size->{width},$size->{height},$bg);
    my @bb = $img->stringFT(-$fg,$file,$points,0,$size->{origin}->{x},$size->{origin}->{y},chr($char));

    my $width = $bb[2] - $bb[0];

    printf(OUT "    %2d,", $width);
    my $line = 0;
    my $byte = 0;
    while($line < $size->{height})
    {
        my $data = 0;
        my $bit = 0;
        while($bit < $width)
        {
            my $pixel = $img->getPixel($width-$bit,$line);
            $data = $data << 1;
            if($pixel == $fg)
            {
                $data |= 1;
            }
            $bit++;
        }
        $bit = $size->{bpl};
        while($bit > 0)
        {
            $bit--;
            printf(OUT " 0x%02X,", ($data >> ($bit * 8)) & 0xFF)
        }
        $line++;
    }
    print OUT "\n";

    $char++;
}

print OUT "};\n";

sub findFontSize()
{
    my $font = shift;
    my $points = shift;
 
    my $char = 32;

    my $bottom = 0;
    my $top = 0;
    my $left = 0;
    my $right = 0;

    while($char < 128)
    {
        my @bb = GD::Image->stringFT(-1,$font,$points,0,0,0,chr($char));
        if($bb[1] > $bottom)
        {
            $bottom = $bb[1];
        }
        if($bb[7] < $top)
        {
            $top = $bb[7];
        }
        if($bb[0] < $left)
        {
            $left = $bb[0];
        }
        if($bb[2] > $right)
        {
            $right = $bb[2];
        }
        $char++;
    }

    my $data;
    $data->{top} = $top;
    $data->{bottom} = $bottom;
    $data->{left} = $left;
    $data->{right} = $right;
    $data->{width} = $right - $left;
    $data->{height} = $bottom - $top;
    $data->{origin}->{x} = 0-$left;
    $data->{origin}->{y} = 0-$top;
    return $data;
}
