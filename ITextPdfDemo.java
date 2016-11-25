package pdf;

import java.io.FileOutputStream;
import com.itextpdf.text.Document;
import com.itextpdf.text.Image;
import com.itextpdf.text.Paragraph;
import com.itextpdf.text.pdf.PdfPCell;
import com.itextpdf.text.pdf.PdfPTable;
import com.itextpdf.text.pdf.PdfWriter;

//more sample can be found from http://developers.itextpdf.com/examples/tables-itext5/101-very-simple-table

public class ITextPdfDemo {

      public static void main(String[] args) throws Exception {
        Document document = new Document();
        PdfWriter.getInstance(document, new FileOutputStream("MyFirstJavaPdf.pdf"));
        document.open();

        Paragraph para = new Paragraph("Here is a table sample");
        para.setSpacingAfter(10);
        document.add(para);
        
        Image image = Image.getInstance("small1.jpg");
        image.scalePercent(50);
        image.setAlignment(Image.ALIGN_MIDDLE);
        document.add(image);

        PdfPTable table = new PdfPTable(3);
        PdfPCell cell = new PdfPCell(new Paragraph("First Name"));

        table.addCell(cell);
        table.addCell("Last Name");
        table.addCell("Gender");
        table.addCell("Ram");
        table.addCell("Kumar");
        table.addCell("Male");
        table.addCell("Lakshmi");
        table.addCell("Devi");
        table.addCell("Female");

        document.add(table);
        
        image = Image.getInstance("big1.jpg");  
        image.scalePercent(50);
        document.add(image);

        document.close();
      }
    }


