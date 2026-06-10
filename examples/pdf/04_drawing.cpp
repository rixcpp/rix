/**
 *
 *  @file 04_drawing.cpp
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

  doc.set_title("Rix PDF Drawing Example");

  auto &page = doc.add_page();

  auto y = page.heading(
      page.x_left(),
      page.y_top(),
      "Drawing primitives",
      1);

  y -= 20.0F;

  page.line(
      page.x_left(),
      y,
      page.x_right(),
      y,
      1.5F,
      rixlib::pdf::Color::blue_color());

  y -= 70.0F;

  page.rect(
      page.x_left(),
      y,
      140.0F,
      50.0F);

  page.fill_rect(
      page.x_left() + 170.0F,
      y,
      140.0F,
      50.0F,
      rixlib::pdf::Color::light_gray());

  page.fill_stroke_rect(
      page.x_left() + 340.0F,
      y,
      140.0F,
      50.0F,
      rixlib::pdf::Color::white(),
      rixlib::pdf::Color::black());

  y -= 100.0F;

  page.circle(
      page.x_left() + 70.0F,
      y,
      35.0F,
      1.0F,
      rixlib::pdf::Color::red_color());

  page.circle(
      page.x_left() + 230.0F,
      y,
      35.0F,
      1.0F,
      rixlib::pdf::Color::green_color(),
      true);

  page.circle(
      page.x_left() + 390.0F,
      y,
      35.0F,
      1.0F,
      rixlib::pdf::Color::blue_color());

  auto saved = rix.pdf.save(doc, "rix_pdf_drawing.pdf");

  if (saved.failed())
  {
    rix.debug.eprint(
        "pdf error:",
        rix.pdf.error.to_string(saved.error()),
        saved.error().message());

    return 1;
  }

  rix.debug.print("created:", "rix_pdf_drawing.pdf");
  return 0;
}
