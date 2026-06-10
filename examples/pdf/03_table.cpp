/**
 *
 *  @file 03_table.cpp
 *  @author Gaspard Kirira
 *
 *  Copyright 2026, Gaspard Kirira.
 *  All rights reserved.
 *  https://github.com/rixcpp/rix
 *
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  Rix
 *
 */

#include <rix.hpp>

int main()
{
  auto doc = rix.pdf.document();

  doc.set_title("Rix PDF Table Example");

  auto &page = doc.add_page();

  auto y = page.heading(
      page.x_left(),
      page.y_top(),
      "Project table",
      1);

  y -= 20.0F;

  rixlib::pdf::Table table;

  table.set_column_widths({160.0F,
                           160.0F,
                           160.0F});

  table.add_header({"Name",
                    "Language",
                    "Project"});

  table.add_row({"Ada",
                 "C++",
                 "Rix"});

  table.add_row({"Gaspard",
                 "C++",
                 "Vix.cpp"});

  table.add_row({"Grace",
                 "Systems",
                 "PDF"});

  page.table(
      page.x_left(),
      y,
      table);

  auto saved = rix.pdf.save(doc, "rix_pdf_table.pdf");

  if (saved.failed())
  {
    rix.debug.eprint(
        "pdf error:",
        rix.pdf.error.to_string(saved.error()),
        saved.error().message());

    return 1;
  }

  rix.debug.print("created:", "rix_pdf_table.pdf");
  return 0;
}
