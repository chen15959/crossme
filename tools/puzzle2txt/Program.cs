using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;

namespace puzzle2txt
{
    class Program
    {
        static void Main(string[] args)
        {
            foreach (string arg in args)
            {
                Bitmap src = new Bitmap(arg);

				System.IO.Directory.CreateDirectory(string.Format("c:\\temp\\0812\\{0}", arg));


                PuzzlePicture pp = new PuzzlePicture(src);

				pp.toBlackWhite(0.5);

				pp.saveTo(string.Format("c:\\temp\\0812\\{0}\\black-white.bmp", arg));

				pp.removeBackground(0.2);

				pp.saveTo(string.Format("c:\\temp\\0812\\{0}\\black-white-without-background.bmp", arg));

				pp.splitTitleAndBlocks(arg);

				pp.analyze(arg);

//				pp.saveTo("c:\\temp\\0812\\remove-bkg-0.5-0.5.bmp");

            }



        }
    }
}
