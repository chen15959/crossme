using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;

namespace puzzle2txt
{
    class PuzzlePicture
    {
        Bitmap picture;
		Bitmap original_picture;

		int argbWhite = Color.White.ToArgb();
		int argbBlack = Color.Black.ToArgb();


        public PuzzlePicture(Bitmap image)
        {
            this.picture = image;
			this.original_picture = image;
        }


        private static int max(int a, int b)
        {
            return a > b ? a : b;
        }

        private static int max(int a, int b, int c)
        {
            return max(max(a, b), c);
        }



		//获取图片各行/列上的某颜色像素数量
		private static void summarize(Bitmap pict, int argb, List<int> rows, List<int> cols)
		{
			rows.Clear();
			cols.Clear();

			for (int x = 0; x < pict.Width; ++x)
			{
				cols.Add(0);
			}
			for (int y = 0; y < pict.Height; ++y)
			{
				rows.Add(0);
			}

			for (int y = 0; y < pict.Height; ++y)
			{
				int count = 0;
				for (int x = 0; x < pict.Width; ++x)
				{
					if (pict.GetPixel(x, y).ToArgb() == argb)
					{
						cols[x]++;
						rows[y]++;
					}
				}
			}
		}

		//根据亮度(0~1)二值化处理图片
        public void toBlackWhite(double th)
        {
            for (int x = 0; x < picture.Width; ++x)
            {
                for (int y = 0; y < picture.Height; ++y)
                {
                    Color color = picture.GetPixel(x, y);

					if (color.GetBrightness() > th)
					{
						picture.SetPixel(x, y, Color.White);
					}
					else
					{
						picture.SetPixel(x, y, Color.Black);
					}
                }
            }



        }


		//移除外围
		//规则是在一排像素中，取最长连续的非外圈色，若比例小于th，则认为这一排属于外圈
		static Bitmap removeOuter(Bitmap pict, double th, int outerArgb)
		{
			int x0, x1, y0, y1;

			List<int> a = new List<int>();

			for (int y = 0; y < pict.Height; ++y)
			{
				int maxInnerLen = 0, innerLen = 0;
				for (int x = 0; x < pict.Width; ++x)
				{
					if (pict.GetPixel(x, y).ToArgb() == outerArgb)
					{
						if (maxInnerLen < innerLen)
						{
							maxInnerLen = innerLen;
						}
						innerLen = 0;
					}
					else
					{
						innerLen++;
					}
				}

				if (maxInnerLen > pict.Width * th)
				{
					a.Add(y);
				}
			}


			y0 = a[0];
			y1 = a[a.Count - 1];

			a.Clear();


			for (int x = 0; x < pict.Width; ++x)
			{
				int maxInnerLen = 0, innerLen = 0;
				for (int y = 0; y < pict.Height; ++y)
				{
					if (pict.GetPixel(x, y).ToArgb() == outerArgb)
					{
						if (maxInnerLen < innerLen)
						{
							maxInnerLen = innerLen;
						}
						innerLen = 0;
					}
					else
					{
						innerLen++;
					}
				}

				if (maxInnerLen > pict.Height * th)
				{
					a.Add(x);
				}
			}


			x0 = a[0];
			x1 = a[a.Count - 1];


			Bitmap bitmap = new Bitmap(x1 - x0, y1 - y0);
			Graphics g = Graphics.FromImage(bitmap);
			g.DrawImage(pict, -x0, -y0);
			g.Flush();
			g.Dispose();
			return bitmap;


		}


		//通过移除外围的方法，移除背景部分
		public void removeBackground(double th)
		{
			picture = removeOuter(picture, th, Color.Black.ToArgb());
		}


		Bitmap title;
		Bitmap blocks;
		List<List<Bitmap>> blockMatrix = new List<List<Bitmap>>();



		//分离标题和盘面
		public void splitTitleAndBlocks(string a)
		{
			List<int> row_black_count = new List<int>();
			//int argbBlack = Color.Black.ToArgb();
			double th = 0.95;

			for (int y = 0; y < picture.Height; ++y)
			{
				int blackCount = 0;
				for (int x = 0; x < picture.Width; ++x)
				{
					if (picture.GetPixel(x, y).ToArgb() == argbBlack)
					{
						blackCount++;
					}
				}
				row_black_count.Add(blackCount);
			}

			List<int> row_black_count_1 = new List<int>(row_black_count);
			row_black_count_1.Sort();
			int spliter = row_black_count_1[(int)(row_black_count_1.Count * th)];
			
			for (int y = 0; y < picture.Height; y++)
			{
				if (row_black_count[y] >= spliter)
				{
					title = new Bitmap(picture.Width, y - 1);
					Graphics g1 = Graphics.FromImage(title);
					g1.DrawImage(picture, 0, 0);
					g1.Flush();
					g1.Dispose();

					title.Save(string.Format("c:\\temp\\0812\\{0}\\title.bmp", a));

					break;
				}
			}


			blocks = new Bitmap(picture.Width, picture.Height - title.Height);
			Graphics g2 = Graphics.FromImage(blocks);
			g2.DrawImage(picture, 0, -title.Height);
			g2.Flush();
			g2.Dispose();


			blocks = removeOuter(blocks, 0.5, Color.White.ToArgb());

			blocks.Save(string.Format("c:\\temp\\0812\\{0}\\blocks.bmp", a));
		}


		//分切盘面
		public void analyzeGrid(string a)
		{
			double th = 0.7;


			int[] col_black = new int[blocks.Width];
			int[] row_black = new int[blocks.Height];


			//找到黑色点
			for (int x = 0; x < blocks.Width; ++x)
			{
				for (int y = 0; y < blocks.Height; ++y)
				{
					if (blocks.GetPixel(x, y).ToArgb() == Color.Black.ToArgb())
					{
						col_black[x] = col_black[x] + 1;
						row_black[y] = row_black[y] + 1;
					}
				}
			}


			List<int> col_b2w0 = new List<int>();
			List<int> col_w2b0 = new List<int>();
			List<int> row_b2w0 = new List<int>();
			List<int> row_w2b0 = new List<int>();



			for (int xi = 0; xi < col_black.Length - 1; ++xi)
			{
				if (col_black[xi] > blocks.Height * th && col_black[xi + 1] < blocks.Height * th)
				{
					col_b2w0.Add(xi+1);
				}
				else if (col_black[xi] < blocks.Height * th && col_black[xi + 1] > blocks.Height * th)
				{
					col_w2b0.Add(xi);
				}
			}

			for (int yi = 0; yi < row_black.Length - 1; ++yi)
			{
				if (row_black[yi] > blocks.Width * th && row_black[yi + 1] < blocks.Width * th)
				{
					row_b2w0.Add(yi + 1);
				}
				else if (row_black[yi] < blocks.Width * th && row_black[yi + 1] > blocks.Width * th)
				{
					row_w2b0.Add(yi);
				}
			}


			List<int> col_edge = findEdge(col_b2w0, col_w2b0);
			List<int> row_edge = findEdge(row_b2w0, row_w2b0);

			if (col_edge.Count % 2 == 1)
			{
				col_edge.Add(blocks.Width);
			}

			if (row_edge.Count % 2 == 1)
			{
				row_edge.Add(blocks.Height);
			}


			for (int x1 = 0; x1 < col_edge.Count / 2; x1++)
			{
				blockMatrix.Add(new List<Bitmap>());
			}


			//Graphics g = Graphics.FromImage(blocks);
			System.IO.Directory.CreateDirectory(string.Format("c:\\temp\\0812\\{0}\\blocks", a));
			for (int xi = 0; xi < col_edge.Count; xi += 2)
			{
				for (int yi = 0; yi < row_edge.Count; yi += 2)
				{
					Bitmap block = new Bitmap(col_edge[xi + 1] - col_edge[xi], row_edge[yi + 1] - row_edge[yi]);
					Graphics g0 = Graphics.FromImage(block);
					g0.DrawImage(blocks, -col_edge[xi], -row_edge[yi]);
					g0.Flush();
					g0.Dispose();

					blockMatrix[xi/2].Add(block);

					block.Save(string.Format("c:\\temp\\0812\\{0}\\blocks\\block-{1}-{2}.bmp", a, xi/2, yi/2));



					//g.DrawRectangle(new Pen(Color.Red), col_b2w[xi], row_b2w[yi],  col_w2b[xi] - col_b2w[xi], row_w2b[yi] - row_b2w[yi]);
				}
			}
			//g.Flush();
			//g.Dispose();


			//blocks.Save("c:\\temp\\0812\\grid.bmp");







		}




		private static List<int> findEdge(List<int> b2w, List<int> w2b)
		{
			List<int> ret = new List<int>();

			if (w2b[0] < b2w[0])
			{
				ret.Add(0);
				ret.Add(w2b[0]);
				w2b.RemoveAt(0);
			}


			while (b2w.Count > 0 && w2b.Count > 0)
			{
				ret.Add(b2w[0]);
				ret.Add(w2b[0]);
				b2w.RemoveAt(0);
				w2b.RemoveAt(0);
			}

			if (b2w.Count == 1 && w2b.Count == 0)
			{
				ret.Add(b2w[0]);
			}

			return ret;



		}







		public void saveTo(string filename)
		{
			picture.Save(filename);
		}
    }
}
