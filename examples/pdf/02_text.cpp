/**
 *
 *  @file 02_text.cpp
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

  doc.set_title("Rix PDF Text Example");
  doc.set_author("Rix");

  auto &page = doc.add_page();

  auto y = page.y_top();

  y = page.heading(
      page.x_left(),
      y,
      "Rix PDF",
      1);

  y -= 10.0F;

  y = page.paragraph(
      page.x_left(),
      y,
      page.content_width(),
      "Rix gives Vix C++ projects a unified userland facade. "
      "The PDF module keeps the public API simple while the writer internals stay hidden.");

  y -= 20.0F;

  page.paragraph(
      page.x_left(),
      y,
      page.content_width(),
      "This paragraph is centered to show text alignment.",
      rixlib::pdf::Align::Center,
      rixlib::pdf::TextStyle{
          rixlib::pdf::Font::Helvetica,
          12.0F,
          rixlib::pdf::Color::blue_color()});

  auto saved = rix.pdf.save(doc, "rix_pdf_text.pdf");

  if (saved.failed())
  {
    rix.debug.eprint(
        "pdf error:",
        rix.pdf.error.to_string(saved.error()),
        saved.error().message());

    return 1;
  }

  rix.debug.print("created:", "rix_pdf_text.pdf");
  return 0;
}
